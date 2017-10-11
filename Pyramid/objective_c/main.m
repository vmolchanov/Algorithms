#include "Pyramid.h"
#include <Foundation/Foundation.h>


int main(int argc, char *argv[]) {
    Pyramid *p = [[Pyramid alloc] init];

    [p insertValue:10];
    [p insertValue:11];
    [p insertValue:13];
    [p insertValue:18];
    [p insertValue:7];
    [p insertValue:14];
    [p insertValue:12];
    [p insertValue:29];
    [p insertValue:18];
    [p insertValue:42];

    NSLog(@"%ld", [p extractMax]);
    NSLog(@"%ld", [p extractMax]);
    NSLog(@"%ld", [p extractMax]);
    NSLog(@"%ld", [p extractMax]);
    NSLog(@"%ld", [p extractMax]);
    NSLog(@"%ld", [p extractMax]);
    NSLog(@"%ld", [p extractMax]);
    NSLog(@"%ld", [p extractMax]);
    NSLog(@"%ld", [p extractMax]);
    NSLog(@"%ld", [p extractMax]);
    
    return 0;
}
