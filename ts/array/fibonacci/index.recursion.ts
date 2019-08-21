/* 斐波那契数列的递归解法 */
export function fibonacci(n: number): number {
  if (n === 0) {
    return 0;
  } else if (n === 1) {
    return 1;
  }

  return fibonacci(n - 1) + fibonacci(n - 2);
}

/** 带缓存的递归 */
export function fibonacciWithMemory(num: number, memo: Record<number, number> = {}): number {
  if (memo[num]) return memo[num];
  if (num <= 1) return 1;

  return (memo[num] = fibonacciWithMemory(num - 1, memo) + fibonacciWithMemory(num - 2, memo));
}

/** 迭代器 */
export function* fibonacciGenerator(n: number, current = 0, next = 1): IterableIterator<number> {
  if (n === 0) {
    return current;
  }

  yield current;

  yield* fibonacciGenerator(n - 1, next, current + next);
}
