import { assert as Assert } from 'chai';
import { BitArray } from '../../lib/collections/BitArray';

describe('BitArray', () => {
  describe('Construction', () => {
    it('Should create BitArray with given size when constructed', () => {
      let bits = new BitArray(32);

      Assert.instanceOf(bits, BitArray);
      Assert.equal(bits.getSize(), 32);
    });

    it('Should create BitArray with given size (large array size) when constructed', () => {
      let bits = new BitArray(10000);

      Assert.instanceOf(bits, BitArray);
      Assert.equal(bits.getSize(), 10000);

      Assert.equal(bits.getMemorySize(), 313 * 8);
    });
  });

  describe('Set', () => {
    it('Should set bit on the correct position (1 set)', () => {
      let bits = new BitArray(32);

      bits.set(1, 1);
      let result = bits.isBitSet(1);

      Assert.equal(result, 1);
    });

    it('Should set bit on the correct position (1 set, position > 32)', () => {
      let bits = new BitArray(1000);

      bits.set(868, 1);
      let result = bits.isBitSet(868);

      Assert.equal(result, 1);
    });

    it('Should unset bit on the correct position (1 set, position > 32)', () => {
      let bits = new BitArray(1000);

      bits.set(868, 1);
      bits.set(867, 1);
      let result = bits.isBitSet(868);

      bits.set(868, 0);
      result = bits.isBitSet(868);

      Assert.isTrue(bits.isBitSet(867));
      Assert.equal(result, false);
    });
  });

  describe('Get', () => {
    it('Should get bit with the correct value (more than 32 bits)', () => {
      let bits = new BitArray(32);

      let result = bits.isBitSet(4);
      Assert.equal(result, false);

      bits.set(1, 1);
      result = bits.isBitSet(1);
      Assert.equal(result, true);
    });

    it('Should get bit with the correct value', () => {
      let bits = new BitArray(64);

      let result = bits.isBitSet(6);
      Assert.equal(result, false);

      bits.set(33, 1);
      result = bits.isBitSet(33);
      Assert.equal(result, true);
    });
  });
});
