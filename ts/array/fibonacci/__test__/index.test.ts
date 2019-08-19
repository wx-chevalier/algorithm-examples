import { fibonacci, fibonacciGenerator } from '../index';

it('fibonacci', () => {
  expect(fibonacci(2)).toEqual(1);
});

it('fibonacciGenerator', () => {
  const actualRes = [0, 1, 1, 2, 3, 5, 8, 13, 21, 34];
  const res = [];
  for (let i of fibonacciGenerator(10)) {
    res.push(i);
  }

  expect(res).toEqual(actualRes);
});
