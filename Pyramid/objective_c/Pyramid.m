#import "Pyramid.h"

@implementation Pyramid {
    NSMutableArray *_tree;
    NSUInteger _size;
    NSInteger _capacity;
}

#pragma mark - Custom constructors

- (instancetype)init {
    self = [super init];
    
    if (self) {
        self->_size = 0;
        self->_capacity = 10;
        self->_tree = [[NSMutableArray alloc] initWithCapacity:self->_capacity];
    }
    
    return self;
}

- (instancetype)initWithCapacity:(NSInteger)capacity {
    self = [super init];
    
    if (self) {
        self->_size = 0;
        self->_capacity = capacity;
        self->_tree = [[NSMutableArray alloc] initWithCapacity:self->_capacity];
    }
    
    return self;
}

#pragma mark - public methods

- (void)insertValue:(NSInteger)value {
    [self->_tree addObject:[NSNumber numberWithInteger:value]];
    self->_size++;
    [self siftUpSinceIndex:self->_size - 1];
}


- (NSInteger)extractMax {
    NSInteger max = [[self->_tree objectAtIndex:0] integerValue];
    
    self->_tree[0] = self->_tree[self->_size - 1];
    self->_size--;
    [self siftDownSinceIndex:0];
    
    return max;
}


- (NSInteger)getMax {
    return [self->_tree[0] integerValue];
}


- (BOOL)isEmpty {
    return !self->_size;
}

#pragma mark - private methods

- (NSInteger)getParentIndexByChildIndex:(NSInteger)childIndex {
    return (childIndex - 1) / 2;
}


- (NSInteger)getLeftChildIndexByParentIndex:(NSInteger)parentIndex {
    return 2 * parentIndex + 1;
}


- (NSInteger)getRightChildIndexByParentIndex:(NSInteger)parentIndex {
    return 2 * parentIndex + 2;
}


- (void)siftUpSinceIndex:(NSUInteger)i {
    NSInteger parentIndex = [self getParentIndexByChildIndex:i];
    
    while (i > 0) {
        if ([self->_tree[i] integerValue] < [self->_tree[parentIndex] integerValue]) {
            break;
        }
        
        [self->_tree exchangeObjectAtIndex:i withObjectAtIndex:parentIndex];
        
        i = parentIndex;
        parentIndex = [self getParentIndexByChildIndex:i];
    }
}


- (void)siftDownSinceIndex:(NSInteger)i {
    NSInteger leftChildIndex = [self getLeftChildIndexByParentIndex:i];
    NSInteger rightChildIndex = [self getRightChildIndexByParentIndex:i];
    
    while (true) {
        NSInteger leftChildValue = leftChildIndex < self->_size ? [self->_tree[leftChildIndex] integerValue] : 0;
        NSInteger rightChildValue = rightChildIndex < self->_size ? [self->_tree[rightChildIndex] integerValue] : 0;
        NSInteger currentNodeValue = [self->_tree[i] integerValue];
        
        if (leftChildIndex < self->_size && currentNodeValue < leftChildValue) {
            BOOL isLeftChildLessThanRightChild = rightChildIndex < self->_size && leftChildValue < rightChildValue;
            
            [self swapNodeAtIndex:&i
                  withNodeAtIndex:(isLeftChildLessThanRightChild ? &rightChildIndex : &leftChildIndex)
           updateLeftChildAtIndex:&leftChildIndex
             andRightChildAtIndex:&rightChildIndex];
            
        } else if (rightChildIndex < self->_size && currentNodeValue < rightChildValue) {
            
            [self swapNodeAtIndex:&i
                  withNodeAtIndex:&rightChildIndex
           updateLeftChildAtIndex:&leftChildIndex
             andRightChildAtIndex:&rightChildIndex];
            
        } else {
            break;
        }
    }
}


- (void) swapNodeAtIndex:(NSInteger*)currentNodeIndex
         withNodeAtIndex:(NSInteger*)newNodeIndex
  updateLeftChildAtIndex:(NSInteger*)leftChildIndex
    andRightChildAtIndex:(NSInteger*)rightChildIndex {
    
    [self->_tree exchangeObjectAtIndex:*currentNodeIndex withObjectAtIndex:*newNodeIndex];
    *currentNodeIndex = *newNodeIndex;
    *leftChildIndex = [self getLeftChildIndexByParentIndex:*currentNodeIndex];
    *rightChildIndex = [self getRightChildIndexByParentIndex:*currentNodeIndex];
}

@end
