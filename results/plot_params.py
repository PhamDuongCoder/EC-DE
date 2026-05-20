import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns

df = pd.read_csv("params_experiment.csv")

# Tính mean best_fitness theo F, CR, function
mean_df = df.groupby(["function", "F", "CR"])["best_fitness"].mean().reset_index()

functions = ["Sphere", "Rosenbrock", "Rastrigin"]
fig, axes = plt.subplots(1, 3, figsize=(18, 5))

for ax, func in zip(axes, functions):
    data = mean_df[mean_df["function"] == func]
    pivot = data.pivot(index="F", columns="CR", values="best_fitness")
    
    sns.heatmap(pivot, ax=ax, annot=True, fmt=".2e", cmap="YlOrRd")
    ax.set_title(f"{func}")
    ax.set_xlabel("CR")
    ax.set_ylabel("F")

plt.suptitle("DE Parameter Sensitivity: Mean Best Fitness over 10 runs")
plt.tight_layout()
plt.savefig("heatmap_params.png", dpi=150)
plt.show()