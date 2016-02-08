import numpy as np 
import os
from sklearn import svm
from sklearn.ensemble import AdaBoostClassifier
from sklearn.neighbors import KNeighborsClassifier

ada = AdaBoostClassifier()
knn = KNeighborsClassifier(n_neighbors=10)
#clf = svm.SVC(kernel = 'poly',class_weight={1:0.9, 2:0.1})
clf2 = svm.SVC(kernel = 'poly')

method = clf2
filepath = "./1/2.5s/"
num = 35
acc_train = []
acc_test = []
acc_number_of_windows_train = []
acc_number_of_windows_test = []
acc_number_of_files_each_sample_train = []
acc_result_of_positive = []
result_acc_test = []

acc_train = np.loadtxt(filepath+str(1)+"accfeature"+"0.txt")
acc_test = np.loadtxt(filepath+str(1)+"accfeature"+"1.txt")
for i in range(1,num+1):
	sample1 = np.loadtxt(filepath+str(i)+"accfeature"+"0.txt")
	sample2 = np.loadtxt(filepath+str(i)+"accfeature"+"1.txt")
	
	if not np.array_equal(acc_train,sample1):
		acc_train = np.concatenate((acc_train,sample1),0)
	acc_number_of_windows_train.append(sample1.shape[0])
	
	if os.path.exists(filepath+str(i)+"accfeature"+"2.txt"):
		sample3 = np.loadtxt(filepath+str(i)+"accfeature"+"2.txt")
		acc_train = np.concatenate((acc_train,sample2),0)
		acc_test = np.concatenate((acc_test,sample3),0)
		acc_number_of_windows_train.append(sample2.shape[0])
		acc_number_of_windows_test.append(sample3.shape[0])
		acc_number_of_files_each_sample_train.append(2)
	else:
		if  not np.array_equal(acc_test,sample2):
			acc_test = np.concatenate((acc_test,sample2),0)
		acc_number_of_files_each_sample_train.append(1)
		acc_number_of_windows_test.append(sample2.shape[0])

index = 0
window_num_train = 0
window_num_test = 0

print acc_number_of_windows_test
for i in range(0,num):
	index = index + acc_number_of_files_each_sample_train[i];
	window_train_size = acc_number_of_windows_train[index-1]
	if acc_number_of_files_each_sample_train[i] == 2:
		window_train_size = window_train_size + acc_number_of_windows_train[index-2]
	window_test_size = acc_number_of_windows_test[i]
	window_num_train = window_num_train+window_train_size
	window_num_test = window_num_test+window_test_size
	#positive_sample = acc_train[window_num_train - window_train_size:window_num_train,:]
	test_sample = acc_test[window_num_test - window_test_size:window_num_test,:]
	#print test_sample.shape
	label = []
	for j in range (0,acc_train.shape[0]):
		label.append(2)
	for j in range (window_num_train - window_train_size,window_num_train):
		label[j] = 1
	method.fit(acc_train,label);
	answer = method.predict(test_sample)
	num_positive = 0.0
	
	for j in range(0,window_test_size):
		if answer[j] == 1:
			num_positive = num_positive + 1
	print i
	acc_result_of_positive.append(num_positive)
	if (num_positive/answer.shape[0]) > 0.5:
		result_acc_test.append(1)
	else :
		result_acc_test.append(2)

Sum = 0.0
for i in range(0,len(result_acc_test)):
	if result_acc_test[i] == 1:
		Sum = Sum + 1

print "result of accfeature"
print Sum/len(result_acc_test)

turn_train = []
turn_test = []
turn_number_of_windows_train = []
turn_number_of_windows_test = []
turn_number_of_files_each_sample_train = []
turn_result_of_positive = []
result_turn_test = []

turn_train = np.loadtxt(filepath+str(1)+"turnfeature"+"0.txt")
turn_test = np.loadtxt(filepath+str(1)+"turnfeature"+"1.txt")
for i in range(1,num+1):
	sample1 = np.loadtxt(filepath+str(i)+"turnfeature"+"0.txt")
	sample2 = np.loadtxt(filepath+str(i)+"turnfeature"+"1.txt")
	
	if not np.array_equal(turn_train,sample1):
		turn_train = np.concatenate((turn_train,sample1),0)
	turn_number_of_windows_train.append(sample1.shape[0])
	
	if os.path.exists(filepath+str(i)+"turnfeature"+"2.txt"):
		sample3 = np.loadtxt(filepath+str(i)+"turnfeature"+"2.txt")
		turn_train = np.concatenate((turn_train,sample2),0)
		turn_test = np.concatenate((turn_test,sample3),0)
		turn_number_of_windows_train.append(sample2.shape[0])
		turn_number_of_windows_test.append(sample3.shape[0])
		turn_number_of_files_each_sample_train.append(2)
	else:
		if  not np.array_equal(turn_test,sample2):
			turn_test = np.concatenate((turn_test,sample2),0)
		turn_number_of_files_each_sample_train.append(1)
		turn_number_of_windows_test.append(sample2.shape[0])

index = 0
window_num_train = 0
window_num_test = 0

for i in range(0,num):
	index = index + turn_number_of_files_each_sample_train[i];
	window_train_size = turn_number_of_windows_train[index-1]
	if turn_number_of_files_each_sample_train[i] == 2:
		window_train_size = window_train_size + turn_number_of_windows_train[index-2]
	window_test_size = turn_number_of_windows_test[i]
	window_num_train = window_num_train+window_train_size
	window_num_test = window_num_test+window_test_size
	#positive_sample = turn_train[window_num_train - window_train_size:window_num_train,:]
	test_sample = turn_test[window_num_test - window_test_size:window_num_test,:]
	#print test_sample.shape
	label = []
	for j in range (0,turn_train.shape[0]):
		label.append(2)
	for j in range (window_num_train - window_train_size,window_num_train):
		label[j] = 1
	method.fit(turn_train,label)
	answer = method.predict(test_sample)
	num_positive = 0.0
	
	for j in range(0,window_test_size):
		if answer[j] == 1:
			num_positive = num_positive + 1
	print i
	turn_result_of_positive.append(num_positive)
	if (num_positive/answer.shape[0]) > 0.5:
		result_turn_test.append(1)
	else :
		result_turn_test.append(2)

Sum = 0.0
for i in range(0,len(result_turn_test)):
	if result_turn_test[i] == 1:
		Sum = Sum + 1

print "result of turnfeature"
print Sum/len(result_turn_test)

result_of_two = []
for i in range(0,num):
	sum_positive = acc_result_of_positive[i]+turn_result_of_positive[i]
	if float(sum_positive)/float((acc_number_of_windows_test[i]+turn_number_of_windows_test[i])) > 0.5:
		result_of_two.append(1)
	else:
		result_of_two.append(2)
Sum = 0.0
for i in range(0,num):
	if result_of_two[i] == 1:
		Sum = Sum + 1

print "result of both features"
print Sum/num

# print len(acc_number_of_windows_test)
# print turn_number_of_windows_test
# print len(turn_number_of_windows_test)



# print acc_result_of_positive
# print turn_result_of_positive


# print acc_train.shape
# #acc_train = np.concatenate((acc_train,sample2))
# print acc_test.shape

# print acc_number_of_windows_train

#print acc_number_of_windows_test

# print acc_number_of_files_each_sample_train



