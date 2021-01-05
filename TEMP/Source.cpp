struct node // структура для представления узлов дерева
{
	int key; // ключ узла
	unsigned char height; // высота поддерева с корнем в данном узле
	node* left; // левое поддерево
	node* right; // правое поддерево
	
	node(int k) // контруктор - новый узел (высоты 1) с заданным ключом k.
	{ 
		key = k; 
		left = right = 0; 
		height = 1; 
	} 
};

unsigned char height(node* p) // обертка для поля height, может работать с нулевыми указателями (с пустыми деревьями)
{
	if (p)
		return p->height;
	else
		return 0;
}

// balance factor - разница высот правого и левого поддеревьев (может быть -1, 0 и 1)
int bfactor(node* p) // вычисляет balance factor заданного узла (и работает только с ненулевыми указателями)
{
	return height(p->right) - height(p->left);
}

void fixheight(node* p) // восстанавливает корректное значение поля height заданного узла (при условии, что значения этого поля в правом и левом дочерних узлах являются корректными)
{
	unsigned char hl = height(p->left);
	unsigned char hr = height(p->right);
	if (hl > hr)
		p->height = hl + 1;
	else
		p->height = hr + 1;
}

node* rotateright(node* p) // правый поворот вокруг p
{
	node* q = p->left;
	p->left = q->right;
	q->right = p;
	fixheight(p); 
	fixheight(q);
	return q;
}

node* rotateleft(node* q) // левый поворот вокруг q
{
	node* p = q->right;
	q->right = p->left;
	p->left = q;
	fixheight(q);
	fixheight(p);
	return p;
}

node* balance(node* p) // балансировка узла p
{
	fixheight(p);
	if (bfactor(p) == 2)
	{
		if (bfactor(p->right) < 0)
			p->right = rotateright(p->right);
		return rotateleft(p);
	}
	if (bfactor(p) == -2)
	{
		if (bfactor(p->left) > 0)
			p->left = rotateleft(p->left);
		return rotateright(p);
	}
	return p; // балансировка не нужна
}

node* insert(node* p, int k) // вставка ключа k в дерево с корнем p
{
	if (!p) return new node(k); // если дерево пустое
	if (k < p->key)
		p->left = insert(p->left, k);
	else
		p->right = insert(p->right, k);
	return balance(p);
}

node* findmin(node* p) // поиск узла с минимальным ключом в дереве p 
{
	if (p->left)
		return findmin(p->left);
	else
		return p;
}

node* removemin(node* p) // удаление узла с минимальным ключом из дерева p
{
	if (p->left == 0)
		return p->right;
	p->left = removemin(p->left);
	return balance(p);
}

node* remove(node* p, int k) // удаление ключа k из дерева p
{
	if (!p) return 0;
	if (k < p->key)
		p->left = remove(p->left, k);
	else if (k > p->key)
		p->right = remove(p->right, k);
	else //  k == p->key 
	{
		node* q = p->left;
		node* r = p->right;
		delete p;
		if (!r) return q;
		node* min = findmin(r);
		min->right = removemin(r);
		min->left = q;
		return balance(min);
	}
	return balance(p);
}

int main() {

	return 0;
}