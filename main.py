import streamlit as st
import matplotlib.pyplot as plt
import pandas as pd
import numpy as np
import json
import subprocess

# from streamlit.runtime.state import session_state

st.write("Hola, este es un proyecto de streamlit")


with open("lista.json", "r", encoding="utf-8") as archivo:
    lista = json.load(archivo)
# print(lista["funciones"])
lista_funciones = [funcion["name"] for funcion in lista["funciones"]]

# imagen = 0


def change_function_image():
    opcion = st.session_state.selector_func
    command = [
        "./build/Algorithms",
        "-s",
        str(
            next(
                lista["funciones"].index(d)
                for d in lista["funciones"]
                if d.get("name") == opcion
            )
        ),
        "100",
    ]
    subprocess.run(command)
    st.session_state.imagen = pd.read_csv("image_funcion.csv")


if "imagen" not in st.session_state:
    st.session_state.imagen = None
st.selectbox(
    "selecciona la función",
    lista_funciones,
    key="selector_func",
    on_change=change_function_image,
)

if st.session_state.imagen is not None:
    imagen = st.session_state.imagen
    fig, ax = plt.subplots()

    # ax.imshow(imagen.pivot(columns="x", index="y", values="f"))
    ax.scatter(imagen.x, imagen.y, c=np.log(imagen.f))

    st.pyplot(fig)


# if st.button("Visualizar"):
#     command = [
#         "./build/Algorithms",
#         "-s",
#         str(
#             next(
#                 lista["funciones"].index(d)
#                 for d in lista["funciones"]
#                 if d.get("name") == opcion
#             )
#         ),
#         "100",
#     ]
#     subprocess.run(command)
#
#     imagen = pd.read_csv("image_funcion.csv")
#     fig, ax = plt.subplots()
#
#     # ax.imshow(imagen.pivot(columns="x", index="y", values="f"))
#     ax.scatter(imagen.x, imagen.y, c=np.log(imagen.f))
#
#     st.pyplot(fig)
