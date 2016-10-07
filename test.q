function fak(n)
	if n == 1
		return 1
	return n * fak(n - 1)

function binomk(n, k)
	return fak(n) / (fak(n - k) * fak(k))

i = 0
while i < 1000
	if i % 2 == 0
		print(i)
	else
		print("urgs")
	print("\n")
	i = i + 1