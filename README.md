# quick
simple, not efficient and not easy-to-integrate scripting language

```
function fak(n)
	if n == 1
		return 1
	return n * fak(n - 1)

function binomk(n, k)
	return fak(n) / (fak(n - k) * fak(k))

i = 10
while i >= 5
	print(i)
	i -= 1
```
