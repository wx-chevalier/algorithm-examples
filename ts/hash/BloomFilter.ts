import { BitArray } from './collections/BitArray';
let farmhash = require('farmhash');
let crypto = require('crypto');

/**
 * A BloomFilter for instances of type T.
 *
 * A Bloom filter is a space-efficient probabilistic data structure that is used to test whether an element is a member
 * of a set.
 *
 * False positives are possible but false negatives not. In laymen's terms this means that an element maybe be in the set
 * or definitely not in the set. The underlying hash function is the Google's FarmHash family of hash functions.
 *
 * The interface is modeled after the BloomFilter in the Google Guava library.
 *
 * References:
 *  - https://en.wikipedia.org/wiki/Bloom_filter
 *  - http://stackoverflow.com/questions/658439/how-many-hash-functions-does-my-bloom-filter-need
 *  - http://stackoverflow.com/questions/15952524/bloom-filter-evaluating-false-positive-rate/24071581#24071581
 *
 * @since 1.0
 */
export class BloomFilter<T> {
  private _fpp: number;
  private data: BitArray;
  private inserted: number = 0;

  private hashFunctions: { (data: string): number }[] = [];

  private expectedInsertions;

  /**
   * Create a new bloom filter of type T. When the false positive probability is not given it will initialize with a
   * default probability of 3% (0.03).
   *
   * @param expectedInsertions
   * @param fpp false positive probability
   */
  constructor(expectedInsertions: number, fpp?: number) {
    this.expectedInsertions = expectedInsertions;

    if (fpp == undefined) {
      this._fpp = 0.03;

      this.initialize(expectedInsertions, this._fpp);
    } else {
      this._fpp = fpp;

      this.initialize(expectedInsertions, fpp);
    }
  }

  /**
   * The expected false positive probability rate. Calculated with the number of expected insertions.
   *
   * @return {number}
   */
  public expectedFpp(): number {
    return this.calculateErrorRate(
      this.expectedInsertions,
      this.data.getSize()
    );
  }

  /**
   * The current false positive probability rate. Calculated using the actual number insertions. This number should be
   * lower then the expectedFpp until the amount of expected insertions is reached.
   *
   * @return {number}
   */
  public currentFpp(): number {
    return this.calculateErrorRate(this.inserted, this.data.getSize());
  }

  /**
   * Get the amount of inserted objects.
   *
   * @return {number}
   */
  public getInsertedAmount(): number {
    return this.inserted;
  }

  /**
   * Returns {@code true} if the element might have been put in this Bloom filter.
   *
   * @return {number}
   */
  public mightContain(object: T): boolean {
    let objectString = this.createObjectString(object);

    for (let i = 0; i < this.hashFunctions.length; i++) {
      let index = this.hashFunctions[i](objectString);

      if (this.data.isBitSet(index) == false) {
        return false;
      }
    }

    return true;
  }

  /**
   * Put element in the bloom filter.
   *
   * @param object
   */
  public put(object: T): void {
    let objectString = this.createObjectString(object);

    for (let i = 0; i < this.hashFunctions.length; i++) {
      let index = this.hashFunctions[i](objectString);

      this.data.set(index, 1);
    }

    this.inserted++;
  }

  /**
   * Put a collection of elements in the filter.
   *
   * @param that
   */
  public putAll(that: T[]): void {
    that.forEach(item => this.put(item));
  }

  private createObjectString(object: T): string {
    return JSON.stringify(object);
  }

  private initialize(expectedInsertions: number, fpp: number) {
    let numberOfBits = this.calculateNumberOfBits(expectedInsertions, fpp);
    let hashFunctions = this.calculateOptimalNumberHashFunctions(
      numberOfBits,
      expectedInsertions
    );

    this.data = new BitArray(numberOfBits);
    this.initializeHashFunctions(hashFunctions, numberOfBits);
  }

  private initializeHashFunctions(hashFunctions: number, numberOfBits: number) {
    // By using double hashing we only need 2 hash functions to create an unlimited number of hash functions.
    let hashFunction1 = this.createHashFunction();
    let hashFunction2 = this.createHashFunction();

    // Create HashFunctions
    for (let i = 0; i < hashFunctions; i++) {
      this.hashFunctions[i] = (data: string) => {
        return (hashFunction1(data) + i * hashFunction2(data)) % numberOfBits;
      };
    }
  }

  private createHashFunction(): (data: string) => number {
    let seed = Math.floor(Math.random() * 1000000);

    return function(data: string): number {
      let buffer = Buffer.from(data);

      return farmhash.hash32WithSeed(buffer, seed);
    };
  }

  /**
   * Calculate the expected probability of false positives.
   *
   * See for more information: https://en.wikipedia.org/wiki/Bloom_filter#Probability_of_false_positives
   *
   * p = e^(-(m / n) * (ln(2)^2))
   *
   * @param expectedInsertions
   * @param numberOfBits
   */
  private calculateErrorRate(expectedInsertions: number, numberOfBits: number) {
    return Math.pow(
      Math.E,
      -(numberOfBits / expectedInsertions) * Math.pow(Math.log(2), 2)
    );
  }

  /**
   * Calculate the optimal number of bits
   *
   * m = -n*ln(p) / (ln(2)^2)
   *
   * where m is the number of bits.
   *
   * @param expectedInsertions
   * @param fpp
   * @return {number}
   */
  private calculateNumberOfBits(
    expectedInsertions: number,
    fpp: number
  ): number {
    return Math.ceil(
      (-1 * expectedInsertions * Math.log(fpp)) / Math.pow(Math.log(2), 2)
    );
  }

  /**
   * Calculate optimal number of hash functions.
   *
   * k = m/n * ln(2)
   *
   * where k is the number of hash functions.
   *
   * @param numberOfBits
   * @param expectedInsertions
   */
  private calculateOptimalNumberHashFunctions(
    numberOfBits: number,
    expectedInsertions: number
  ): number {
    return Math.ceil((numberOfBits / expectedInsertions) * Math.log(2));
  }
}
