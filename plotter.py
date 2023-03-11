import matplotlib.pyplot as plt
import log

speed = []
voltage = []

for element in log.y:
    speed.append(element[1])
    voltage.append(element[0])
 
x = range(len(speed))
plt.plot(x,speed,linewidth = 2, color = "#333555")
 
x = range(0, len(voltage) * 10, 10)
plt.plot(x,voltage, color = "#aaaaaa", linewidth = 2)
 
plt.show()
