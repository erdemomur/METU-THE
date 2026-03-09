import java.util.ArrayList;

public class ScholarNodePrimaryIndex extends ScholarNode {
	private ArrayList<Integer> paperIds;
	private ArrayList<ScholarNode> children;
	
	public ScholarNodePrimaryIndex(ScholarNode parent) {
		super(parent);
		paperIds = new ArrayList<Integer>();
		children = new ArrayList<ScholarNode>();
		this.type = ScholarNodeType.Internal;
	}

	public ScholarNodePrimaryIndex(ScholarNode parent, ArrayList<Integer> paperIds, ArrayList<ScholarNode> children) {
		super(parent);
		this.paperIds = paperIds;
		this.children = children;
		this.type = ScholarNodeType.Internal;
	}
	
	// GUI Methods - Do not modify
	public ArrayList<ScholarNode> getAllChildren()
	{
		return this.children;
	}
	
	public ScholarNode getChildrenAt(Integer index) {return this.children.get(index); }
	
	public Integer paperIdCount()
	{
		return this.paperIds.size();
	}

	public Integer paperIdAtIndex(Integer index) {
		if(index >= this.paperIdCount() || index < 0) {
			return -1;
		}
		else {
			return this.paperIds.get(index);
		}
	}
	
	// Extra functions if needed
	public void addPaperId(Integer paperId) {
		this.paperIds.add(paperId);
	}
	public void addPaperId(Integer index, Integer paperId) {
		this.paperIds.add(index, paperId);
	}
	public void addChild(ScholarNode child) {
		this.children.add(child);
	}
	public void addChild( Integer index,ScholarNode child) {
		this.children.add(index, child);
	}
	public void deleteChild(ScholarNode child) {
		this.children.remove(child);
	}
	public ArrayList<Integer> getAllPaperIDs() {
		return this.paperIds;
	}
}
