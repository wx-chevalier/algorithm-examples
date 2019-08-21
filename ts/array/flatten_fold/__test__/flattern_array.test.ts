import { flatternArrayByReduce } from '../flattern_array';

it('flatternArrayByReduce', () => {
  const expectArr = [0, 1, 2, 3];
  expect(flatternArrayByReduce([0, [1, 2], 3])).toEqual(expectArr);
});
