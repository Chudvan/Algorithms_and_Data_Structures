Node getMinimum(H : BinomialHeap):
	min_key = float("inf")
	min_node = null
	curH = H.head
	while curH != null:
		if curH.key < min_key:
			min_node = curH
			min_key = curH.key
		curH = curH.sibling
	return min_node

BinomialHeap merge(H1 : BinomialHeap, H2 : BinomialHeap):
	if H1 == null:
		return H2
	if H2 == null:
		return H1
	H.head = null
	curH = H.head
	curH1 = H1.head
	curH2 = H2.head
	while curH1 != null and curH2 != null:
		if curH1.degree < curH2.degree:
			curH.sibling = curH1
			curH = curH1
			curH1 = curH1.sibling
		else:
			curH.sibling = curH2
			curH = curH2
			curH2 = curH2.sibling
	if curH1 == null:
		while curH2 != null:
			curH.sibling = curH2
			curH = curH2
			curH2 = curH2.sibling
	else:
		while curH1 != null:
			curH.sibling = curH1
			curH = curH1
			curH1 = curH1.sibling
	# завершено соединение корневых списков куч в единый список, в котором корневые вершины идут в порядке неубывания их степеней.
	curH = H.head
	while curH.sibling != null:
		if curH.degree == curH.sibling.degree:
			less, second = min(curH, curH.sibling) # min(a : Node, b : Node) - возвращает пару принятых узлов в порядке, где первым идёт узел с меньшим key
			second.sibling = less.child
			less.child = second
			second.parent = less
			# Остаётся правильное формированиt списка корней (предыдущий_узел.sibling == less, а less.sibling == curH.sibling.sibling)
			# + решить задачу правильного перехода на следующий узел (если это объединение привело к появлению 3-х деревьев одного порядка, то в какой последовательности складывать их?) - переполнение при сложении двоичных чисел
		# как правильно менять curH ?
	return H
		
BinomialHeap insert(H : BinomialHeap, el : Node):
	H_new = BinomialHeap(el)
	return merge(H, H_new)

Node extractMin(H : BinomialHeap):
	min_key = float("inf")
	x = null
	xBefore = null
	curx = H.head
	curxBefore = null
	while curx != null:
		if curx.key < min_key:
			min_key = curx.key
			x = curx
			xBefore = curxBefore
		curxBefore = curx
		curx = curx.sibling
	if x == null: # куча H пуста
		return x
	if xBefore == null: # удаление найденного корня x из списка корней деревьев кучи
		H.head = x.sibling
	else:
		xBefore.sibling = x.sibling
	H' = BinomialHeap(null) # построение кучи детей вершины x, при этом изменяем предка соответствующего ребенка на null:
	curx = x.child
	curxBefore = null
	curxNext = null
	while curx != null: # Необходимо развернуть список корней детей т.к. при проходе по нему степени соответствующих корней находятся в возрастающем порядке
		curx.parent = null # меняем указатель на родителя узла curx 
		curxNext = curx.sibling
		curx.sibling = curxBefore
		curxBefore = curx
		curx = curxNext
	H'.head = curxBefore
	H = merge(H, H')
	return x

void decreaseKey(H : BinomialHeap, x : Node, k : int):
	if k >= x.key:
		return
	x.key = k
	y = x
	z = y.parent
	while z != null and y.key < z.key:
		y.key, z.key = z.key, y.key # swap
		y = z
		z = y.parent

void delete(H : BinomialHeap, x : Node):
	decreaseKey(H, x, -float("inf"))
	extractMin(H)

