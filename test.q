function fak(n)
	if n == 1
		return 1
	return n * fak(n - 1)

function binomk(n, k)
	return fak(n) / (fak(n - k) * fak(k))

print(binomk(10, 4))