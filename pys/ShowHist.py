import numpy as np
import matplotlib.pyplot as plt


def showgragh(x):
	# mu, sigma = 100, 15
	# x = mu + sigma * np.random.randn(10000)
	print(len(x))
	n, bins, patches = plt.hist(x, 200, facecolor='b', alpha=0.7)
	plt.xlabel('Ride Count')
	plt.ylabel('Count')
	plt.title('Task2, Lazy Strategy, in 12:00 - 18:00')
	# plt.text(60, .025, r'$\mu=100,\ \sigma=15$')
	#plt.axis([0, 600, 0, 400])
	plt.grid(True)
	plt.show()

#	printf("%d %d %d %d %.2lf %.2lf\n", ondelivertime[tc][i], ongoingtime[tc][i], kongtime[tc][i], cnt[tc][i], driverdis[tc][i], money[tc][i]);

def main():
	tasknum = "Task2_2"
	toplot = []

	for i in range(4):
		# if i == 0:
		# 	print "0:00 - 6:00 :",
		# if i == 1:
		# 	print "6:00 - 12:00 :",
		# if i == 2:
		# 	print "12:00 - 18:00 :",
		# if i == 3:
		# 	print "18:00 - 24:00 :",
		for t in range(6):
			# if t == 0:
			# 	print "delivertime =",
			# if t == 1:
			# 	print "goingtime =",
			# if t == 2:
			# 	print "waitingtime =",
			# if t == 3:
			# 	print "ridecount =",
			# if t == 4:
			# 	print "driverdis =",
			# if t == 5:
			# 	print "income =",
			x = []
			filename = "../data/results/"+ tasknum + "result" + str(i + 1) + ".txt"
			with open(filename, "r") as f:
				lines = f.read()
				lines = lines.split('\n')
				for j in lines:
					#print(j)
					if len(j) < 2:
						continue
					tmp = list(map(float,j.split(" ")))
					if t == 5 and tmp[t] < 1:
						continue;
					if tmp[5] < 0 or tmp[5] > 1e10:
						continue;
					x.append(tmp[t])
				x = np.array(x)
				#print(x)
			print np.mean(x),
			print "\t",

		print("")
	#showgragh(x)


main()
