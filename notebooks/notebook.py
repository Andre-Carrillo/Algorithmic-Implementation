import marimo

__generated_with = "0.23.13"
app = marimo.App(width="medium")


@app.cell
def _():
    import marimo as mo
    import Algorithms as alg
    import matplotlib.pyplot as plt
    import numpy as np

    return alg, np, plt


@app.cell
def _(alg):
    alg.lista()
    return


@app.cell
def _(alg):
    contexto = alg.contextoAlg()
    contexto.radio = 0.5
    contexto.max_iter = 40
    contexto.pop_size = 200
    contexto.max_generations = 200
    contexto.tasa_reduccion = 0.8
    contexto.alpha = 0.90
    contexto.max_list_tabu = 20
    contexto.n_tweaks_sample = 10
    return (contexto,)


@app.cell
def _():
    algoritmo_id = 2
    problema_id = 1
    return algoritmo_id, problema_id


@app.cell
def _(alg, algoritmo_id, contexto, plt, problema_id):
    simulacion = alg.simular(algoritmo_id, problema_id, contexto)
    plt.plot(simulacion["tiempo"], simulacion["best_score"])
    return (simulacion,)


@app.cell
def _(alg, np, plt, problema_id, simulacion):
    imagen = alg.map_problema(problema_id, 100)
    plt.scatter(imagen["x"], imagen["y"], c = np.log(imagen["f"]))
    plt.plot(simulacion["best_x"], simulacion["best_y"], c="red")
    return


if __name__ == "__main__":
    app.run()
