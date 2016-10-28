# a = raw_input()

a="abdb"
def check_palindrome(a):
	flag=0
	for i,each in enumerate(a):
		if(i/2 > len(a)/2):
			break
		# print(each,a[-i-1])
		if(each != a[-i-1]):
			flag = 1
			break
	if(flag==1):
		return 0
	else:
		return 1
temp=''
def min_substring(a):
	temp=a
	q=''
	for i,each in enumerate(a):
		q = each+q
		print(temp+q)
		if(check_palindrome(temp+q)):
			return a[:i+1]
		q=q[:-1]
		temp=temp[1:]
	# return a[:-1]+a[::-1]

a = min_substring("race")
print(a[::-1])
