declare namespace farmhash {
  export function hash32(input: String | Buffer): number;
  export function hash32WithSeed(input: String | Buffer, seed: number): number;

  export function hash64(input: String | Buffer): string;
  export function hash64WithSeed(input: String | Buffer, seed: number): string;

  export function hash32v1(input: String | Buffer): number;

  export function fingerprint32(input: String | Buffer): number;
  export function fingerprint64(input: String | Buffer): number;
}
