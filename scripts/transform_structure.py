# script de un solo uso para convertir un archivo representando la estructura
# de dependencias con varios niveles de anidamiento a otro con un solo nivel
from collections import defaultdict
import re


def leer_estructura(ruta: str) -> list[str]:
    with open(ruta, "r") as archivo:
        return archivo.readlines()


def extraer_nombre_archivo(linea: str) -> str:
    linea_sin_parentesis = re.sub(r"\s*\([^)]*\)", "", linea)
    return linea_sin_parentesis.split("-")[1].strip()


def procesar_lineas(lineas: list[str]) -> dict[str, list[str]]:
    estructura: dict[str, list[str]] = defaultdict(list)
    pila: list[str] = []
    for linea in lineas:
        if linea.startswith("##"):
            break
        if linea.strip() == "" or linea.strip().startswith("#"):
            continue

        nivel = linea.count("    ")  # Asumiendo 4 espacios por nivel de anidamiento
        nombre_archivo = extraer_nombre_archivo(linea)

        if nivel == 0:
            pila = [nombre_archivo]
        else:
            if len(pila) > nivel:
                pila = pila[:nivel]
            padre = pila[-1]
            pila.append(nombre_archivo)
            estructura[padre].append(nombre_archivo)

    return estructura


def escribir_nueva_estructura(estructura: dict[str, list[str]], ruta_salida: str):
    with open(ruta_salida, "w") as archivo:
        for padre, dependencias in estructura.items():
            archivo.write(f"- {padre}:\n")
            for dep in set(dependencias):
                archivo.write(f"    - {dep}\n")
            archivo.write(f"\n")


def main() -> None:
    ruta_entrada = input_path
    ruta_salida = output_path

    lineas = leer_estructura(ruta_entrada)
    estructura = procesar_lineas(lineas)
    escribir_nueva_estructura(estructura, ruta_salida)


input_path = "dev/old_estructura.md"
output_path = "dev/estructura_modificada.md"


if __name__ == "__main__":
    main()
