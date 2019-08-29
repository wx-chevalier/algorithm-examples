/* 斐波那契数列的循环解法 */
export function fibonacci(n: number) {
  let current = 0;
  let next = 1;

  while (n--) {
    [current, next] = [next, current + next];
  }

  return current;
}

/** 循环生成器 */
export function* fibonacciGenerator(n: number) {
  // 当未输入 n 时，默认为无限循环
  const infinite = !n && n !== 0;

  let current = 0;
  let next = 1;

  while (infinite || n--) {
    yield current;
    [current, next] = [next, current + next];
  }
}
