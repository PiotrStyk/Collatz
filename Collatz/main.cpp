#include <iostream>
using namespace std;
#define OMIT 4294967295
struct Heaps
{
	unsigned int value;
	int index;
	int minIndex;
	int maxIndex;
};
int getParent(int idx)
{
	return((idx - 1) / 2);
}
int getLeftChild(int idx)
{
	return((idx * 2) + 1);
}
int getRightChild(int idx)
{
	return((idx * 2) + 2);
}
int getMinIndex(Heaps Heap[], int ind)
{
	return Heap[ind].minIndex;
}
int getMaxIndex(Heaps Heap[], int ind)
{
	return Heap[ind].maxIndex;
}
int getIndex(Heaps Heap[], int ind)
{
	return Heap[ind].index;
}
void swapmin(int a, int b, Heaps MinHeap[], Heaps MaxHeap[])
{
	MinHeap[a].minIndex = b;
	MinHeap[b].minIndex = a;
	Heaps tmp;
	tmp = MinHeap[a];
	MinHeap[a] = MinHeap[b];
	MinHeap[b] = tmp;
	swap(MaxHeap[MinHeap[a].maxIndex].minIndex, MaxHeap[MinHeap[b].maxIndex].minIndex);
}
void swapmax(int a, int b, Heaps MinHeap[], Heaps MaxHeap[])
{
	MaxHeap[a].maxIndex = b;
	MaxHeap[b].maxIndex = a;
	Heaps tmp;
	tmp = MaxHeap[a];
	MaxHeap[a] = MaxHeap[b];
	MaxHeap[b] = tmp;
	swap(MinHeap[MaxHeap[a].minIndex].maxIndex, MinHeap[MaxHeap[b].minIndex].maxIndex);
}
void pushmax(unsigned int value, int i, int size, Heaps MaxHeap[])
{
	MaxHeap[size].value = value;
	MaxHeap[size].index = i;
	MaxHeap[size].maxIndex = size;
	MaxHeap[size].minIndex = size;
}

void pushmin(unsigned int value, int i, int size, Heaps MinHeap[])
{
	MinHeap[size].value = value;
	MinHeap[size].index = i;
	MinHeap[size].minIndex = size;
	MinHeap[size].maxIndex = size;
}

void push(unsigned int value, int i, int size, Heaps MinHeap[], Heaps MaxHeap[])
{
	pushmax(value, i, size, MaxHeap);
	pushmin(value, i, size, MinHeap);
}
void maxUp(int idx,Heaps MinHeap[], Heaps MaxHeap[])
{
	if (idx == 0) return;
	int parent = getParent(idx);
	if (MaxHeap[idx].value >= MaxHeap[parent].value)
	{
		if (MaxHeap[idx].value > MaxHeap[parent].value || (MaxHeap[idx].value == MaxHeap[parent].value && MaxHeap[idx].index < MaxHeap[parent].index))
		{
			swapmax(idx,parent,MinHeap,MaxHeap);
			maxUp(parent,MinHeap,MaxHeap);
		}
	}
}
void minUp(int idx, Heaps MinHeap[], Heaps MaxHeap[])
{
	if (idx == 0) return;
	int parent = getParent(idx);
	if (MinHeap[idx].value <= MinHeap[parent].value)
	{
		if (MinHeap[idx].value < MinHeap[parent].value || (MinHeap[idx].value == MinHeap[parent].value && MinHeap[idx].index < MinHeap[parent].index))
		{
			swapmin(idx, parent, MinHeap, MaxHeap);
			minUp(parent, MinHeap, MaxHeap);
		}
	}
}
void maxDown(int idx, int size, Heaps MinHeap[], Heaps MaxHeap[])
{
	int change = idx;
	int l = 2 * idx + 1;
	int r = 2 * idx + 2;
	if (l <= size - 1 && MaxHeap[l].value > MaxHeap[change].value)
	{
		change = l;
	}
	else if (l <= size - 1 && MaxHeap[l].value == MaxHeap[change].value)
	{
		if (MaxHeap[l].index < MaxHeap[change].index)
		{
			change = l;
		}
	}
	if (r <= size - 1 && MaxHeap[r].value > MaxHeap[change].value)
	{
		change = r;
	}
	else if (r <= size - 1 && MaxHeap[r].value == MaxHeap[change].value)
	{
		if (MaxHeap[r].index < MaxHeap[change].index)
		{
			change = r;
		}
	}
	if (change != idx)
	{
		
		swapmax(change, idx, MinHeap, MaxHeap);
		maxDown(change, size, MinHeap, MaxHeap);
	}
	
}
void minDown(int idx, int size, Heaps MinHeap[], Heaps MaxHeap[])
{
	int change = idx;
	int l = 2 * idx + 1;
	int r = 2 * idx + 2;

	if (l <= size - 1 && MinHeap[l].value < MinHeap[change].value)
	{
		change = l;
	}
	else if (l <= size - 1 && MinHeap[l].value == MinHeap[change].value)
	{
		if (MinHeap[l].index < MinHeap[change].index)
		{
			change = l;
		}
	}
	if (r <= size - 1 && MinHeap[r].value < MinHeap[change].value)
	{
		change = r;
	}
	else if (r <= size - 1 && MinHeap[r].value == MinHeap[change].value)
	{
		if (MinHeap[r].index < MinHeap[change].index)
		{
			change = r;
		}
	}
	if (change != idx)
	{
		
		swapmin(change, idx, MinHeap, MaxHeap);
		minDown(change, size, MinHeap, MaxHeap);
	}
	
}
void collatzmin(Heaps MinHeap[], Heaps MaxHeap[], int *size, unsigned int tab[])
{
	int size2 = *size;
	int tmpmax = getMaxIndex(MinHeap, 0);
	int tmp = getIndex(MinHeap, 0);
	if (size2 == 0)
	{
		return;
	}
	if (MinHeap[0].value % 2 == 0)
	{
		MinHeap[0].value = MinHeap[0].value / 2;
		MaxHeap[tmpmax].value = MaxHeap[tmpmax].value / 2;
		tab[tmp] /= 2;
		if (MinHeap[0].value == 1)
		{
			if (tmpmax != size2 - 1)
			{
				swapmax(tmpmax, size2 - 1, MinHeap, MaxHeap);
				maxDown(tmpmax, size2, MinHeap, MaxHeap);
				maxUp(tmpmax, MinHeap, MaxHeap);
			}
			swapmin(0, size2 - 1, MinHeap, MaxHeap);
			
			(*size)--;
			size2--;
			
			minDown(0, size2, MinHeap, MaxHeap);
			
			return;
		}
		else
		{

			maxDown(tmpmax,size2, MinHeap, MaxHeap);
		}
	}
	else if (MinHeap[0].value % 2 == 1)
	{
		if (MinHeap[0].value > OMIT/3)
		{
			tab[tmp] = 0;
			MinHeap[0].value = 0;
			MaxHeap[tmpmax].value = 0;
			if (tmpmax != size2 - 1)
			{
				swapmax(tmpmax, size2 - 1, MinHeap, MaxHeap);
				maxUp(tmpmax, MinHeap, MaxHeap);
				maxDown(tmpmax, size2, MinHeap, MaxHeap);
			}
			swapmin(0, size2 - 1, MinHeap, MaxHeap);			
			(*size)--;
			size2--;
			
			minDown(0, size2, MinHeap, MaxHeap);
			
			return;
		}
		else
		{
			MinHeap[0].value = 3 * MinHeap[0].value + 1;
			MaxHeap[tmpmax].value = 3 * MaxHeap[tmpmax].value + 1;
			tab[tmp] = 3 * tab[tmp] + 1;
			maxUp(tmpmax, MinHeap, MaxHeap);
			minDown(0, size2, MinHeap, MaxHeap);
			
		}
	}

}
void collatzmax(Heaps MaxHeap[], Heaps MinHeap[], int *size, unsigned int tab[])
{
	int size2 = *size;
	int tmpmin = getMinIndex(MaxHeap, 0);
	int tmp = getIndex(MaxHeap, 0);
	if (size2 == 0)
	{
		return;
	}
	if (MaxHeap[0].value % 2 == 0)
	{
		MaxHeap[0].value = MaxHeap[0].value / 2;
		MinHeap[tmpmin].value = MinHeap[tmpmin].value / 2;
		tab[tmp] /= 2;
		if (MaxHeap[0].value == 1)
		{
			
			if (tmpmin != (size2 - 1))
			{
				swapmin(tmpmin, size2 - 1, MinHeap, MaxHeap);
				minDown(tmpmin, size2, MinHeap, MaxHeap);
				minUp(tmpmin, MinHeap, MaxHeap);
			}
			swapmax(0, size2 - 1, MinHeap, MaxHeap);
			(*size)--;
			size2--;
			
			maxDown(0, size2, MinHeap, MaxHeap);
			return;
		}
		else
		{

			minUp(tmpmin,  MinHeap, MaxHeap);
			maxDown(0, size2, MinHeap, MaxHeap);
		}
	}
	else if (MaxHeap[0].value % 2 == 1)
	{
		if (MaxHeap[0].value > OMIT/3)
		{
			tab[tmp] = 0;
			MaxHeap[0].value = 0;
			MinHeap[tmpmin].value = 0;
			

			if (tmpmin != (size2 - 1))
			{
				swapmin(tmpmin, size2 - 1, MinHeap, MaxHeap);
				minUp(tmpmin, MinHeap, MaxHeap);
				minDown(tmpmin, size2, MinHeap, MaxHeap);
			}
			
			swapmax(0, size2 - 1, MinHeap, MaxHeap);
			(*size)--;
			size2--;
						
			maxDown(0, size2, MinHeap, MaxHeap);
			return;
		}
		else
		{
			MaxHeap[0].value = 3 * MaxHeap[0].value + 1;
			MinHeap[tmpmin].value = 3 * MinHeap[tmpmin].value + 1;
			tab[tmp] = 3 * tab[tmp] + 1;
			minDown(tmpmin,size2,  MinHeap, MaxHeap);
		}
	}
}

void sortHeap(Heaps MinHeap[], Heaps MaxHeap[], int size)
{
	for (int i = getParent(size); i >= 0; i--)
	{
		maxDown(i, size, MinHeap, MaxHeap);
		minDown(i, size, MinHeap, MaxHeap);
	}
}

int main()
{
	int n;
	cin >> n;
	if (n > 60000)
	{
		return 0;
	}
	Heaps *MaxHeap, *MinHeap;
	MaxHeap = new Heaps[n];
	MinHeap = new Heaps[n];
	int s = 0;
	int *size;
	size = &s;

	unsigned int* tab = new unsigned int[n];
	for (int i = 0; i < n; i++)
	{
		cin >> tab[i];
		if (tab[i] != 1)
		{
			push(tab[i], i, *size, MinHeap, MaxHeap);
			s++;
		}
	}

	int q;
	cin >> q;
	if (q > 2000)
	{
		return 0;
	}
	if (q != 0)
	{
		sortHeap(MinHeap, MaxHeap, *size);

		int k;
		char c;
		for (int i = 0; i < q; i++)
		{
			cin >> k >> c;
			if (k > 2000)
			{
				return 0;
			}
			for (int j = 0; j < k; j++)
			{
				if (c == 's')
				{
					collatzmin(MinHeap, MaxHeap, size, tab);
				}
				else if (c == 'l')
				{
					collatzmax(MaxHeap, MinHeap, size, tab);
				}
				else
				{
					return 0;
				}
			}
		}
	}
	for (int i = 0; i < n; i++)
	{
		if (tab[i] == 0)
		{
			cout << "m ";
		}
		else
		{
			cout << tab[i] << " ";
		}

	}
		delete[] tab;
		delete[] MaxHeap;
		delete[] MinHeap;
		return 0;
	
}