package nju.iip.kevin.ac;

import java.util.Iterator;

/**
 * AhoCorasick(AC)�㷨����Ҫʵ���ࡣ
 * */
public class AhoCorasick {
	
	
	/**
	 * ����������
	 */
	/*AC�������ĸ��ڵ�*/
	private State root;
	/*prepared����ָ���������Ƿ������*/
	private boolean prepared;

	/**
	 * �����������
	 */
	
	/*�޲ι��캯��*/
	public AhoCorasick() {
		
		/*����һ�����Ϊ0�������*/
		this.root = new State(0);
		/*������������δ����*/
		this.prepared = false;
	}

	/**
	 * @author kevin_bear(����������)
	 * @function �������keyword����ӵ��������У�output���ؽ����ʹ����������
	 * 			 SearchResults.getOutputs()���ص�ʧ�ܽ��
	 */
	public void add(byte[] keyword, Object output) {
		if (this.prepared){
			throw new IllegalStateException("can't add keywords after prepare() is called.");
		}
		State lastState = this.root.extendAll(keyword);
		lastState.addOutput(output);
	}

	/**
	 * Prepares the automaton for searching. This must be called before any
	 * searching().
	 */
	public void prepare() {
		this.prepareFailTransitions();
		this.prepared = true;
	}

	/**
	 * Starts a new search, and returns an Iterator of SearchResults.
	 */
	public Iterator search(byte[] bytes) {
		return new Searcher(this, this.startSearch(bytes));
	}

	/**
	 * DANGER DANGER: dense algorithm code ahead. Very order dependent.
	 * Initializes the fail transitions of all states except for the root.
	 */
	private void prepareFailTransitions() {
		Queue q = new Queue();
		for (int i = 0; i < 256; i++) {
			if (this.root.get((byte) i) != null) {
				this.root.get((byte) i).setFail(this.root);
				q.add(this.root.get((byte) i));
			}else{
				this.root.put((byte) i, this.root);
			}
		}
		
		while (!q.isEmpty()) {
			State state = q.pop();
			byte[] keys = state.keys();			
			for (int i = 0; i < keys.length; i++) {				
				State r = state;
				byte a = keys[i];
				State s = r.get(a);
				q.add(s);
				r = r.getFail();
				while (r.get(a) == null)
					r = r.getFail();
				s.setFail(r.get(a));
				s.getOutputs().addAll(r.get(a).getOutputs());
			}
		}
	}

	/**
	 * Returns the root of the tree. Package protected, since the user probably
	 * shouldn't touch this.
	 */
	State getRoot() {
		return this.root;
	}

	/**
	 * Begins a new search using the raw interface. Package protected.
	 */
	SearchResult startSearch(byte[] bytes) {
		if (!this.prepared){
			throw new IllegalStateException("can't start search until prepare()");
		}
		return continueSearch(new SearchResult(this.root, bytes, 0));
	}

	/**
	 * Continues the search, given the initial state described by the
	 * lastResult. Package protected.
	 */
	SearchResult continueSearch(SearchResult lastResult) {
		byte[] bytes = lastResult.bytes;
		State state = lastResult.lastMatchedState;
		for (int i = lastResult.lastIndex; i < bytes.length; i++) {
			byte b = bytes[i];					
			while (state.get(b) == null){
				state = state.getFail();
			}
			state = state.get(b);			
			if (state.getOutputs().size() > 0){	
				return new SearchResult(state, bytes, i + 1);
			}
			
		}
		return null;
	}

	public static void main(String args[])
	{
	       AhoCorasick tree = new AhoCorasick();
	       tree.add("������".getBytes(), "������");
	       tree.add("�Ŷ���".getBytes(), "�Ŷ���");
	       tree.prepare();

	       Iterator searcher = tree.search("���찮�����ն����������Ŀ�����Ŷ���".getBytes());
	       while (searcher.hasNext()) {
	           SearchResult result = (SearchResult) searcher.next();
	           System.out.println(result.getOutputs());
	           System.out.println("Found at index: " + result.getLastIndex());
	       }
	}
}
