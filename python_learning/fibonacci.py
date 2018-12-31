# fibonacci.py
# Ryan Jensen
# 2018-12-31
# This function calculates Fibonacci number n.
def fibonacci(n):
	"""Print a Fibonacci series up to n."""
	
	minimum = 1
	if n < minimum:
		print("n cannot be less than", minimum)
		return 0
	
	if not( (type(n) is int) or (type(n) is float) ):
		print("input number must be a number!")
		return 0
	
	if int(n) != n:
		print("input number must be an integer")
		return 0
	
	a,b = 0,1
	for i in range(n-1):
		a,b = b,b+a
	
	return b
#

