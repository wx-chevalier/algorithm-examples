module.exports = {
  coverageDirectory: '<rootDir>/@coverage',
  globals: {
    'ts-jest': {
      tsConfig: 'tsconfig.test.json'
    }
  },
  moduleFileExtensions: ['js', 'ts'],
  rootDir: './',
  testRegex: '/__test__/.+\\.(test|spec)\\.ts$',
  transform: { '^.+\\.ts$': 'ts-jest' },
  verbose: true
};
