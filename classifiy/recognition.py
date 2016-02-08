import numpy as np
from sklearn import svm
from sklearn.ensemble import AdaBoostClassifier
#from sklearn import dataset
from sklearn.neighbors import KNeighborsClassifier
from sklearn.qda import QDA

a = np.loadtxt("1.txt",dtype = float)


label = []
label.append(1)
for n in range(2,49):
	filename = str(n)+".txt"
	a = np.concatenate((a,np.loadtxt(filename,dtype = float)),0)
	label.append(1)

dirve_pre = a;


b = np.loadtxt("zou.txt")
label.append(2)
for n in range(2,11):
	filename = "zou"+str(n) + ".txt"
	b = np.concatenate((b,np.loadtxt(filename,dtype = float)),0)
	label.append(2)
print(b)

walk_pre = b

a = np.concatenate((a,b),1)

a.shape = 58,236






print(label)

print(a.shape)

ada = AdaBoostClassifier()
ada.fit(a,label)

knn = KNeighborsClassifier(n_neighbors=10)
knn.fit(a,label)

clf = svm.SVC(kernel='poly')
clf.fit(a,label)


# drive_test =  np.loadtxt("49.txt")

# for n in range(50,103):
# 	filename = str(n)+".txt"
# 	drive_test = np.concatenate((drive_test,np.loadtxt(filename,dtype = float)),0)

# drive_test.shape = 53,236


# walk_test = np.loadtxt("zou11.txt")

# for n in range(13,19):
# 	filename = "zou"+str(n) + ".txt"
# 	walk_test = np.concatenate((walk_test,np.loadtxt(filename,dtype = float)),0)

# walk_test.shape = 6,236


#clf.fit(walk_test);
#clf.score()



driving = 0
walk = 0

for n in range(1,49):
 	filename = str(n) +".txt"
 	c = np.loadtxt(filename,dtype = float) 
 	answer = clf.predict(c)
 	if answer[0] == 1:
 		driving = driving+1
		pass

print (driving/48.0)

driving = 0;

for n in range(49,103):
 	filename = str(n) +".txt"
 	c = np.loadtxt(filename,dtype = float) 
 	answer = clf.predict(c)
 	if answer[0] == 1:
 		driving = driving+1
		pass
 	#print(answer)

print (float(driving/54.0))


for n in range(1,11):
	filename = "zou"+str(n) +".txt"
	c = np.loadtxt(filename,dtype = float)
	answer = clf.predict(c)
	if answer[0] == 2:
		walk = walk + 1 
		pass

print(walk/10.0)

walk = 0

#print (float(walk/10.0))

for n in range(11,19):
	filename = "zou"+str(n) +".txt"
	c = np.loadtxt(filename,dtype = float)
	answer = clf.predict(c)
	if answer[0] == 2:
		walk = walk + 1 
		pass

print (float(walk/8.0))


