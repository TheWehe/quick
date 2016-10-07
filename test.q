function f(x)
	return x

i = 0
while i < 3
	if i == 1
		print("break")
		break
	print(f(i))
	i = i + 1