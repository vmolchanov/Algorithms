#include <iostream>
#include <algorithm>


class Pyramid {
    
public:
    Pyramid(const int capacity = 10) {
        this->_size = 0;
        this->_capacity = capacity;
        this->_tree = new int[capacity];
    }
    
    
    ~Pyramid() {
        delete [] _tree;
    }
    
    
    /**
     * Метод для вставки элемента в пирамиду
     *
     * @param value - значение, которое будет вставлено в пирамиду
     */
    void insert(const int value) {
        if (this->_size == this->_capacity) {
            this->_capacity *= 2;
            int *newTree = new int[this->_capacity];
            for (int i = 0; i < this->_size; i++) {
                newTree[i] = this->_tree[i];
            }
            delete [] this->_tree;
            this->_tree = newTree;
        }
        
        this->_tree[this->_size] = value;
        this->_size++;
        this->_siftUp(this->_size - 1);
    }
    
    
    /**
     * Метод возвращает максимальное значение пирамиды. При этом это значение будет удалено из пирамиды с сохранением
     * баланса
     *
     * @return максимальное значение в пирамиде
     */
    int extractMax() {
        int max = this->_tree[0];
        
        this->_tree[0] = this->_tree[this->_size - 1];
        this->_size--;
        this->_siftDown(0);
        
        return max;
    }
    
    
    /**
     * Возвращает максимальное значение из пирамиды
     *
     * @return максимальное значение в пирамиде
     */
    int getMax() {
        return this->_tree[0];
    }
    
    
    /**
     * Метод проверяет пирамиду на пустоту
     *
     * @return флаг, характеризующий пустоту пирамиды (true - пустая, иначе false)
     */
    bool isEmpty() {
        return !this->_size;
    }
    
    void print() {
        for (int i = 0; i < this->_size; i++) {
            std::cout << this->_tree[i] << " ";
        }
        std::cout << std::endl;
    }
    
private:
    int *_tree;
    
    int _size;
    int _capacity;
    
    
    /**
     * Метод возвращает индекс родителя
     *
     * @param index - текущий индекс, индекс родителя которого нужно вернуть
     * @return индекс родителя
     *
     * @private
     */
    int _getParentIndex(const int index) const {
        return (index - 1) / 2;
    }
    
    
    /**
     * Метод возвращает индекс левого потомка
     *
     * @param index - текущий индекс, индекс левого потомка которого нужно вернуть
     * @return индекс левого потомка
     *
     * @private
     */
    int _getLeftChildIndex(const int index) const {
        return 2 * index + 1;
    }
    
    
    /**
     * Метод возвращает индекс правого потомка
     *
     * @param index - текущий индекс, индекс правого потомка которого нужно вернуть
     * @return индекс правого потомка
     *
     * @private
     */
    int _getRightChildIndex(const int index) const {
        return 2 * index + 2;
    }
    
    
    /**
     * Метод выполняет всплытие элемента, начиная с заданного индекса.
     *
     * @param i - индекс элемента, с которого нужно начинать всплытие
     *
     * @private
     */
    void _siftUp(int i) {
        int parentIndex = this->_getParentIndex(i);
        
        while (i > 0) {
            if (this->_tree[i] < this->_tree[parentIndex]) {
                break;
            }
            
            std::swap(this->_tree[i], this->_tree[parentIndex]);
            
            i = parentIndex;
            parentIndex = this->_getParentIndex(i);
        }
        
    }
    
    
    /**
     * Метод выполняет погружение элемента, начиная с заданного индекса.
     *
     * @param i - индекс элемента, с которого нужно начинать погружение
     *
     * @private
     */
    void _siftDown(int i) {
        int leftChildIndex = this->_getLeftChildIndex(i);
        int rightChildIndex = this->_getRightChildIndex(i);
        
        while (true) {
            if (leftChildIndex < this->_size && this->_tree[i] < this->_tree[leftChildIndex])
                this->_swapNodes(&i,
                                 rightChildIndex < this->_size && this->_tree[leftChildIndex] < this->_tree[rightChildIndex] ? &rightChildIndex : &leftChildIndex,
                                 &leftChildIndex,
                                 &rightChildIndex);
            else if (rightChildIndex < this->_size && this->_tree[i] < this->_tree[rightChildIndex])
                this->_swapNodes(&i, &rightChildIndex, &leftChildIndex, &rightChildIndex);
            else
                break;
        }
    }
    
    
    /**
     * Метод выполняет перемещение одной ноды с другой и обновляет соответствующие индексы
     *
     * @param currentNodeIndex - индекс текущей ноды
     * @param newNodeIndex - индекс новой ноды
     * @param leftChildIndex - индекс левого потомка текущей ноды
     * @param rightChildIndex - индекс правого потомка текущей ноды
     *
     * @private
     */
    void _swapNodes(int *currentNodeIndex,
                    int *newNodeIndex,
                    int *leftChildIndex,
                    int *rightChildIndex) {
        
        std::swap(this->_tree[*currentNodeIndex], this->_tree[*newNodeIndex]);
        *currentNodeIndex = *newNodeIndex;
        *leftChildIndex = this->_getLeftChildIndex(*currentNodeIndex);
        *rightChildIndex = this->_getRightChildIndex(*currentNodeIndex);
    }
};


int main() {
    Pyramid p;
    
    p.insert(10);
    p.insert(11);
    p.insert(13);
    p.insert(18);
    p.insert(7);
    p.insert(14);
    p.insert(12);
    p.insert(29);
    p.insert(18);
    p.insert(42);
    
    std::cout << p.extractMax() << std::endl;
    std::cout << p.extractMax() << std::endl;
    std::cout << p.extractMax() << std::endl;
    std::cout << p.extractMax() << std::endl;
    std::cout << p.extractMax() << std::endl;
    std::cout << p.extractMax() << std::endl;
    std::cout << p.extractMax() << std::endl;
    std::cout << p.extractMax() << std::endl;
    std::cout << p.extractMax() << std::endl;
    std::cout << p.extractMax() << std::endl;
    
    return 0;
}
