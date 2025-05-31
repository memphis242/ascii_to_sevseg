import matplotlib.pyplot as plt
import csv

# Path to your CSV file
csv_path = 'scripts/ascii7seg_encodings.csv'

x_vals = []
y_vals = []
labels = []
encodings = []

with open(csv_path, newline='') as csvfile:
    reader = csv.reader(csvfile)
    for row in reader:
        if not row or row[0].startswith('//'):
            continue  # Skip comments or empty lines
        x, y, label = int(row[0]), int(row[1]), row[2]
        x_vals.append(x)
        y_vals.append(y)
        labels.append(label)
        encodings.append(y)

plt.figure(figsize=(10, 6))
plt.scatter(x_vals, y_vals)

# Add labels to each point
for i, txt in enumerate(labels):
    plt.annotate(txt, (x_vals[i], y_vals[i]), fontsize=15, ha='right', va='bottom')

plt.xlabel('ASCII Character')
plt.ylabel('Encoding as a Byte')
plt.title('ASCII 7-Segment Encodings Scatter Plot')
plt.grid(True)
plt.tight_layout()
plt.show()

# Additional plots for each bit in the encoding (assuming 7 bits for 7 segments)
fig, axes = plt.subplots(2, 4, figsize=(18, 8))
fig.suptitle('Scatter Plots for Each Bit in Segment Encoding (Second Number)')
for bit in range(7):
    y_bit = [(val >> bit) & 1 for val in encodings]
    ax = axes[bit // 4, bit % 4]
    ax.scatter(x_vals, y_bit)
    for i, txt in enumerate(labels):
        ax.annotate(txt, (x_vals[i], y_bit[i]), fontsize=7, ha='right', va='bottom')
    ax.set_xlabel('First Number (ASCII code)')
    ax.set_ylabel(f'Bit {bit} of Encoding')
    ax.set_title(f'Bit {bit} of Segment Encoding')
    ax.set_yticks([0, 1])
    ax.grid(True)
# Hide the last (unused) subplot if 2x4 grid
axes[1, 3].axis('off')
plt.tight_layout(rect=[0, 0.03, 1, 0.95])
plt.show()