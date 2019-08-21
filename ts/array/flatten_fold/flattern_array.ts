type Atom = number;

interface NestedArray extends Array<NestedArray | Atom> {}

/**
 * 数组扁平化，即将 [2,[3,4],[5,[6,[7]]]] 扁平化为 [2,3,4,5,6,7]
 */

export const flatternArray = (arr: NestedArray) => {
  const result: number[] = [];

  arr.forEach(item => {
    if (Array.isArray(item)) {
      result.push(...flatternArray(item));
    } else {
      result.push(item);
    }
  });

  return result;
};

export const flatternArrayByReduce = (arr: NestedArray): number[] => {
  return arr.reduce<number[]>((prev, itemOrArr) => {
    return Array.isArray(itemOrArr)
      ? [...prev, ...flatternArrayByReduce(itemOrArr)]
      : [...prev, itemOrArr];
  }, []);
};

/**
 * 嵌套数组求和，求 [2,[3,4],[5,[6,[7]]]] 中所有元素相加的和
 */
export const flatternArraySumByReduce = (arr: NestedArray): number => {
  return arr.reduce<number>((prev, itemOrArr) => {
    return Array.isArray(itemOrArr) ? prev + flatternArraySumByReduce(itemOrArr) : prev + itemOrArr;
  }, 0);
};
