package nju.iip.kevin.ac;

/**
 * ʹ���ܼ��������洢�ߵ���Ϣ��
 * ��������ʹ���������洢����Ϣ�����������ٶȷǳ��쵫�Ǵ洢�����ϴ�
 */

class DenseEdgeList implements EdgeList {
	private State[] array;

	public DenseEdgeList() {
		this.array = new State[256];
		for (int i = 0; i < array.length; i++)
			this.array[i] = null;
	}

	/**
	 * Helps in converting to dense representation.
	 */
	public static DenseEdgeList fromSparse(SparseEdgeList list) {
		byte[] keys = list.keys();
		DenseEdgeList newInstance = new DenseEdgeList();
		for (int i = 0; i < keys.length; i++) {
			newInstance.put(keys[i], list.get(keys[i]));
		}
		return newInstance;
	}

	public State get(byte b) {
		return this.array[(int) b & 0xFF];
	}

	public void put(byte b, State s) {
		this.array[(int) b & 0xFF] = s;
	}

	public byte[] keys() {
		int length = 0;
		for (int i = 0; i < array.length; i++) {
			if (array[i] != null)
				length++;
		}
		byte[] result = new byte[length];
		int j = 0;
		for (int i = 0; i < array.length; i++) {
			if (array[i] != null) {
				result[j] = (byte) i;
				j++;
			}
		}
		return result;
	}

}
