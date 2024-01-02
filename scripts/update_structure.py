import os
from pathlib import Path
import re
from typing import Mapping, NewType, Sequence, TypeVar

Formatted = NewType("Formatted", str)
MAIN_FILE = Formatted("main.cpp")
TO_IGNORE = "demos"


def extraer_dependencias_de_archivo(archivo: Path) -> list[Formatted]:
    """
    Extrae las dependencias (includes) de un archivo C++.
    Busca lineas que contienen #include "filename.ext".
    """
    try:
        with open(archivo, "r") as file:
            lineas = file.readlines()
    except FileNotFoundError:
        print(f"Advertencia: No se pudo abrir el archivo {archivo}")
        return []

    dependencias: list[Formatted] = []
    parent = archivo.parent
    for linea in lineas:
        m = re.match('#include "(.+)"', linea)
        if m:
            dependencia = m.groups()[0]
            # Extraer el nombre del archivo incluido.
            formatted = get_path_formatted(Path(os.path.join(parent, dependencia)))
            dependencias.append(formatted)
    return dependencias


def get_path_formatted(path: Path) -> Formatted:
    return Formatted("/".join(path.resolve().relative_to(Path("src").absolute()).parts))


def leer_dependencias(directorio: Path) -> dict[Formatted, list[Formatted]]:
    """
    Lee las dependencias de todos los archivos .cpp y .h en un directorio.
    """
    dependencias: dict[Formatted, list[Formatted]] = {}
    for root, _dirs, archivos in os.walk(directorio):
        for archivo in archivos:
            if not archivo.endswith((".cpp", ".h")):
                continue
            ruta_completa = os.path.join(root, archivo)
            dependencias_archivo = extraer_dependencias_de_archivo(Path(ruta_completa))
            formatted = get_path_formatted(Path(ruta_completa))
            dependencias[formatted] = dependencias_archivo
    return dependencias


T = TypeVar("T", bound=str)


def move_to_beginning(a_list: list[T], item: T) -> None:
    """Mueve el elemento seleccionado al inicio de la lista"""
    assert a_list.count(item) == 1
    a_list.remove(item)
    a_list.insert(0, item)


def to_header(filepath: Formatted) -> Formatted:
    assert filepath.count(".") == 1
    archivo_sin_ext = filepath.split(".")[0]
    return Formatted(archivo_sin_ext + ".h")


def format_dependencies_as_text(
    dependencias: Mapping[Formatted, Sequence[Formatted]]
) -> list[str]:
    """
    Estructura las dependencias en un formato de texto.
    """

    estructura: list[str] = []
    archivos_ordenados = sorted(dependencias.keys())
    if MAIN_FILE in archivos_ordenados:
        move_to_beginning(archivos_ordenados, MAIN_FILE)
    archivos_ordenados = [name for name in archivos_ordenados if TO_IGNORE not in name]
    for archivo in archivos_ordenados:
        dependencias_archivo = dependencias.get(archivo)
        if not dependencias_archivo:
            continue
        dependencias_archivo = [
            dep for dep in dependencias_archivo if TO_IGNORE not in dep
        ]
        dependencias_archivo.sort()

        assert dependencias_archivo
        header = to_header(archivo)
        if header in dependencias_archivo:
            move_to_beginning(dependencias_archivo, header)

        estructura.append(f"- {archivo}:")
        for dependencia in dependencias_archivo:
            estructura.append(f"    - {dependencia}")
        estructura.append("")
    return estructura


def main() -> None:
    """
    Funcion principal del script.
    """
    directorio_actual = Path(os.getcwd()) / "src"
    dependencias = leer_dependencias(directorio_actual)
    estructura = format_dependencies_as_text(dependencias)
    print("\n".join(estructura))


if __name__ == "__main__":
    main()
