import numpy as np 
from sklearn import svm
from sklearn.ensemble import AdaBoostClassifier
#from sklearn import dataset
from sklearn.neighbors import KNeighborsClassifier

kern = 'poly'

filepath = "5s"
filepathzuo = "zuo"
filepathzou = "zou"
filepathdrive = "drive"
label = []
label1 = []
label2 = []
label_drive = []
label_zou = []
label_zuo = []

result_drive=[]
result_zou=[]
result_zuo=[]

result_drive_secondlayer = []
result_zou_secondlayer = []

zuo_sum = 16
drive_sum = 107
zou_sum = 28

clf = svm.SVC(kernel = kern)
knn = KNeighborsClassifier(n_neighbors=10)
ada = AdaBoostClassifier()
method = ada


#read drive features
filename = "./"+filepath +filepathdrive+ "/"+str(1)+".txt"
drive_train = np.loadtxt(filename)
label_drive.append(1)
winnum = drive_train.shape[0]
#print winnum
for n in range(2,81):
	filename = "./"+filepath +filepathdrive+ "/"+str(n)+".txt"
	#print np.loadtxt(filename).shape
	drive_train = np.concatenate((drive_train,np.loadtxt(filename)),0)
	label_drive.append(1)

filename = "./"+filepath +filepathdrive+ "/"+str(81)+".txt"
drive_test = np.loadtxt(filename)
for n in range(82,108):
	filename = "./"+filepath +filepathdrive+ "/"+str(n)+".txt"
	drive_test = np.concatenate((drive_test,np.loadtxt(filename)),0)

#read zou features
filename = "./"+filepath +filepathzou+ "/"+str(1)+".txt"
zou_train = np.loadtxt(filename)
label_zou.append(2)

for n in range(2,24):
	filename = "./"+filepath +filepathzou+ "/"+str(n)+".txt"
	#print np.loadtxt(filename).shape
	zou_train = np.concatenate((zou_train,np.loadtxt(filename)),0)
	label_zou.append(2)

filename = "./"+filepath +filepathzou+ "/"+str(24)+".txt"
zou_test = np.loadtxt(filename)
for n in range(25,29):
	filename = "./"+filepath +filepathzou+ "/"+str(n)+".txt"
	zou_test = np.concatenate((zou_test,np.loadtxt(filename)),0)



#read zuo features
filename = "./"+filepath +filepathzuo+ "/"+str(1)+".txt"
zuo_train = np.loadtxt(filename)
label_zuo.append(3)

for n in range(2,12):
	filename = "./"+filepath +filepathzuo+ "/"+str(n)+".txt"
	#print np.loadtxt(filename).shape
	zuo_train = np.concatenate((zuo_train,np.loadtxt(filename)),0)
	label_zuo.append(3)

filename = "./"+filepath +filepathzuo+ "/"+str(12)+".txt"
zuo_test = np.loadtxt(filename)
for n in range(13,17):
	filename = "./"+filepath +filepathzuo+ "/"+str(n)+".txt"
	zuo_test = np.concatenate((zuo_test,np.loadtxt(filename)),0)


# print label_drive
# print label_zou
# print label_zuo

for n in range(0,drive_train.shape[0]):
	label1.append(1)
	label2.append(1)
for n in range(0,zou_train.shape[0]):
	label1.append(1)
	label2.append(2)
for n in range(0,zuo_train.shape[0]):
	label1.append(2)

firstlayer = np.concatenate((drive_train,zou_train),0)
firstlayer = np.concatenate((firstlayer,zuo_train),0)

method.fit(firstlayer,label1)

#print len(label_drive)
answer = method.predict(drive_test)
for i in range(0,drive_sum-len(label_drive)):
	num = 0.0
	for j in range(i*winnum,(i+1)*winnum):
		if answer[j] == 1:
			num = num+1
	if (num/winnum)>0.5:
		result_drive.append(1)
	else:
		result_drive.append(2)

print result_drive

answer = method.predict(zou_test)
for i in range(0,zou_sum-len(label_zou)):
	num = 0.0
	for j in range(i*winnum,(i+1)*winnum):
		if answer[j] == 1:
			num = num+1
	if (num/winnum)>0.5:
		result_zou.append(1)
	else:
		result_zou.append(2)

print result_zou

answer = method.predict(zuo_test)
for i in range(0,zuo_sum-len(label_zuo)):
	num = 0.0
	for j in range(i*winnum,(i+1)*winnum):
		if answer[j] == 1:
			num = num+1
	if (num/winnum)>0.5:
		result_zuo.append(1)
	else:
		result_zuo.append(2)

print result_zuo

##second layer##

secondlayer = np.concatenate((drive_train,zou_train),0)
method.fit(secondlayer,label2)

for i in range(0,len(result_drive)):
	if result_drive[i] == 1:
		drive_secondlayer_test = drive_train[i*winnum:(i+1)*winnum,:]
		answer = method.predict(drive_secondlayer_test)
		num = 0.0
		for j in range(0,winnum):
			if answer[j] == 1:
				num = num+1
		if (num/winnum) > 0.5:
			result_drive_secondlayer.append(1)
		else:
			result_drive_secondlayer.append(2)
	else:
		result_drive_secondlayer.append(3)


print result_drive_secondlayer

for i in range(0,len(result_zou)):
	if result_zou[i] == 1:
		zou_secondlayer_test = zou_train[i*winnum:(i+1)*winnum,:]
		answer = method.predict(zou_secondlayer_test)
		num = 0.0
		for j in range(0,winnum):
			if answer[j] == 2:
				num = num+1
		if (num/winnum) > 0.5:
			result_zou_secondlayer.append(2)
		else:
			result_zou_secondlayer.append(1)
	else:
		result_zou_secondlayer.append(3)

print result_zou_secondlayer

num = 0.0
for i in range(0,len(result_drive_secondlayer)):
	if result_drive_secondlayer[i] == 1:
		num= num+1
print "driving result:"
print num/len(result_drive_secondlayer)

num = 0.0
for i in range(0,len(result_zou_secondlayer)):
	if result_zou_secondlayer[i] == 2:
		num =num+1
print "walking result:"
print num/len(result_zou_secondlayer)

num = 0.0
for i in range(0,len(result_zuo)):
	if result_zuo[i] == 2:
		num = num+1
print "sitting result:"
print num/len(result_zuo)


# print answer.shape
# answer = method.predict(zou_test)
# print answer
# answer = method.predict(zuo_test)
# print answer




# print drive_test.shape
# print drive_train.shape
# print zou_test.shape
# print zou_train.shape
# print zuo_test.shape
# print zuo_train.shape













