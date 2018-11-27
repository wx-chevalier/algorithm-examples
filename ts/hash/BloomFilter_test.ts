import { assert as Assert } from 'chai';
import { BloomFilter } from '../lib/BloomFilter';

describe('BloomFilter', () => {
  describe('Construction', () => {
    it('Should create bloomfilter with fpp of 0.03 when initialized', () => {
      let filter = new BloomFilter<Number>(10000);

      Assert.isTrue(isEqualFloat(filter.expectedFpp(), 0.03, 0.0001));
    });
  });

  describe('put', () => {
    it('Should correctly put item in bloom filter', () => {
      let filter = new BloomFilter<string>(1000);

      Assert.equal(filter.getInsertedAmount(), 0);
      let name = 'test';
      filter.put(name);

      Assert.isTrue(filter.mightContain(name));
      Assert.equal(filter.getInsertedAmount(), 1);

      Assert.isFalse(filter.mightContain('BlaBla'));
    });

    it('Should correctly deny that item is in set', () => {
      let filter = new BloomFilter<string>(100);

      Assert.equal(filter.getInsertedAmount(), 0);
      Assert.isFalse(filter.mightContain('BlaBla'));
    });

    it('Should also work with objects', () => {
      let filter = new BloomFilter<TestObject>(1000);

      let object: TestObject = {
        id: 1,
        text: 'Hello'
      };

      filter.put(object);

      let object2: TestObject = {
        id: 1,
        text: 'Hello'
      };

      Assert.isTrue(filter.mightContain(object2));

      let object3: TestObject = {
        id: 2,
        text: 'Hello'
      };

      Assert.isFalse(filter.mightContain(object3));
    });
  });

  describe('putAll', () => {
    it('should all items to the bloomfilter', () => {
      let filter = new BloomFilter<string>(10000);

      let items = ['test-1', 'test-2', 'test-3'];

      filter.putAll(items);

      Assert.isTrue(filter.mightContain('test-1'));
      Assert.isTrue(filter.mightContain('test-2'));
      Assert.isTrue(filter.mightContain('test-3'));
    });
  });

  function isEqualFloat(
    actual: number,
    expected: number,
    epsilon: number
  ): boolean {
    return actual <= expected + epsilon && actual >= expected - epsilon;
  }
});

interface TestObject {
  id: number;
  text: string;
}
