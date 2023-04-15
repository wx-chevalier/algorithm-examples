package nju.iip.kevin.ac;

import java.util.HashSet;
import java.util.Set;

/**
 * State�����AC����ÿһ������״̬��Ϣ
 */

class State {

	/*�ó�����Ϊһ����ֵ�������Ƿ�ʹ��ϡ�����*/
	/*���������ȳ����˼ȶ���ֵ��Ŀǰѡ������3�����Զ�ʹ��ϡ���������ʾ��*/

	private static final int THRESHOLD_TO_USE_SPARSE = 3;

	private int depth;
	private EdgeList edgeList;
	private State fail;
	
	/*outputs��ʾ�ѵ�ǰ���Ϊʧ�ܽ������п��ܷ���ֵ*/
	private Set outputs;
	
	/**
	 * @function ���ι��캯��
	 * @param depth����ʼ�������
	 */
	public State(int depth) {
		this.depth = depth;
		if (depth > THRESHOLD_TO_USE_SPARSE) {
			this.edgeList = new SparseEdgeList();
		} else {
			this.edgeList = new DenseEdgeList();
		}
		this.fail = null;
		this.outputs = new HashSet();
	}

	public State extend(byte b) {
		if (this.edgeList.get(b) != null){
			return this.edgeList.get(b);
		}
		State nextState = new State(this.depth + 1);
		this.edgeList.put(b, nextState);
		return nextState;
	}
	
	/**
	 * 
	 * @param bytes:����Ĺؼ����ֽ�����
	 * @return
	 */
	public State extendAll(byte[] bytes) {
		/*stateָ��ǰ���*/
		State state = this;
		for (int i = 0; i < bytes.length; i++) {
			/*�жϵ�ǰ�Ĺؼ��ֽ��Ƿ��Ѿ��ǵ�ǰ����һ����*/
			if (state.edgeList.get(bytes[i]) != null){
				state = state.edgeList.get(bytes[i]);
			}else{
				state = state.extend(bytes[i]);
			}
		}

		return state;
	}
	/**
	 * Returns the size of the tree rooted at this State. Note: do not call this
	 * if there are loops in the edgelist graph, such as those introduced by
	 * AhoCorasick.prepare().
	 */
	public int size() {
		byte[] keys = edgeList.keys();
		int result = 1;
		for (int i = 0; i < keys.length; i++){
			result += edgeList.get(keys[i]).size();
		}
		return result;
	}

	public State get(byte b) {
		return this.edgeList.get(b);
	}

	public void put(byte b, State s) {
		this.edgeList.put(b, s);
	}

	public byte[] keys() {
		return this.edgeList.keys();
	}

	public State getFail() {
		return this.fail;
	}

	public void setFail(State f) {
		this.fail = f;
	}

	public void addOutput(Object o) {
		this.outputs.add(o);
	}

	public Set getOutputs() {
		return this.outputs;
	}
}
