import java.util.ArrayList;
import java.util.Objects;

public class ScholarTree {
	
	public ScholarNode primaryRoot;		//root of the primary B+ tree
	public ScholarNode secondaryRoot;	//root of the secondary B+ tree
	public ScholarTree(Integer order) {
		ScholarNode.order = order;
		primaryRoot = new ScholarNodePrimaryLeaf(null);
		primaryRoot.level = 0;
		secondaryRoot = new ScholarNodeSecondaryLeaf(null);
		secondaryRoot.level = 0;
	}

	public void addPaper(CengPaper paper) {
		// TODO: Implement this method
		// add methods to fill both primary and secondary tree
		return;
	}

	public CengPaper searchPaper(Integer paperId) {
		// TODO: Implement this method
		// find the paper with the searched paperId in primary B+ tree
		// return value will not be tested, just print according to the specifications
		return null;
	}

	public void searchJournal(String journal) {
		// TODO: Implement this method
		// find the journal with the searched journal in secondary B+ tree
		return;
	}

	public void printPrimaryScholar() {
		// TODO: Implement this method
		// print the primary B+ tree in Depth-first order
		return;
	}

	public void printSecondaryScholar() {
		// TODO: Implement this method
		// print the secondary B+ tree in Depth-first order
		return;
	}
	
	// Extra functions if needed
}


