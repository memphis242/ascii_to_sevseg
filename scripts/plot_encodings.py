import matplotlib.pyplot as plt
import csv

# Path to your CSV file
csv_path = 'scripts/ascii7seg_encodings.csv'

x_vals = []
y_vals = []
labels = []

with open(csv_path, newline='') as csvfile:
    reader = csv.reader(csvfile)
    for row in reader:
        if not row or row[0].startswith('//'):
            continue  # Skip comments or empty lines
        x, y, label = int(row[0]), int(row[1]), row[2]
        x_vals.append(x)
        y_vals.append(y)
        labels.append(label)

plt.figure(figsize=(10, 6))
plt.scatter(x_vals, y_vals)

# Add labels to each point
for i, txt in enumerate(labels):
    plt.annotate(txt, (x_vals[i], y_vals[i]), fontsize=8, ha='right', va='bottom')

plt.xlabel('First Number')
plt.ylabel('Second Number')
plt.title('ASCII 7-Segment Encodings Scatter Plot')
plt.grid(True)
plt.tight_layout()
plt.show()