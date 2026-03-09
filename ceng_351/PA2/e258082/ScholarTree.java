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

		//PRIMARY B+ TREE
		//ROOT LEAF İSE

		if (primaryRoot.getType() == ScholarNodeType.Leaf){
			ScholarNodePrimaryLeaf Tayfun = (ScholarNodePrimaryLeaf) primaryRoot;
			int numberOfPaper = Tayfun.paperCount();
			//ROOT LEAF VE NO SPLİT
			boolean inserted = false;
			for (int i = 0; i<numberOfPaper; i++){
				if (Tayfun.paperIdAtIndex(i) < paper.paperId()){
					continue;
				} else{
					Tayfun.addPaper(i,paper);
					inserted = true;
					break;
				}
			}
			if (!inserted){
				Tayfun.addPaper(numberOfPaper,paper);
			}
			numberOfPaper++;
			//ROOT LEAF İSE VE SPLİT VARSA
			if (numberOfPaper == 2*ScholarNode.order + 1){
				ScholarNodePrimaryIndex newRoot = new ScholarNodePrimaryIndex(null);
				ScholarNodePrimaryLeaf newNodeL = new ScholarNodePrimaryLeaf(newRoot);
				ScholarNodePrimaryLeaf newNodeR = new ScholarNodePrimaryLeaf(newRoot);
				for (int i = 0; i<ScholarNode.order; i++){
					newNodeL.addPaper(i,Tayfun.paperAtIndex(i));
				}
				for (int j=ScholarNode.order, i=0; j<2*ScholarNode.order + 1; j++, i++){
					newNodeR.addPaper(i,Tayfun.paperAtIndex(j));
				}
				newRoot.addPaperId(newNodeR.paperIdAtIndex(0));
				newRoot.addChild(newNodeL);
				newRoot.addChild(newNodeR);
				primaryRoot = newRoot;
			}
			//ROOT LEAF DEĞİL İSE
		} else{
			ScholarNode node = primaryRoot;
			boolean x;
			while(node.getType() == ScholarNodeType.Internal){
				x = false;
				for (int i=0; i<((ScholarNodePrimaryIndex)node).paperIdCount(); i++){
					if (((ScholarNodePrimaryIndex)node).paperIdAtIndex(i) > paper.paperId()){
						node = ((ScholarNodePrimaryIndex)node).getChildrenAt(i);
						x = true;
						break;
					}
				}
				if (!x){
					node = ((ScholarNodePrimaryIndex)node).getChildrenAt(((ScholarNodePrimaryIndex)node).paperIdCount());
				}
			}
			ScholarNodePrimaryLeaf Tayfun = ((ScholarNodePrimaryLeaf) node);

			//LEAF'TE SPLIT YOK
			boolean inserted = false;
			int numberOfPaper = Tayfun.paperCount();
			for (int i = 0; i<numberOfPaper;i++){
				if (Tayfun.paperIdAtIndex(i) < paper.paperId()){
					continue;
				} else {
					Tayfun.addPaper(i,paper);
					inserted = true;
					break;
				}
			}
			if (!inserted){
				Tayfun.addPaper(numberOfPaper,paper);
			}
			//LEAF'TE SPLIT VAR
			if (Tayfun.paperCount() == 2*ScholarNode.order + 1 ){
				ScholarNode parent = Tayfun.getParent();

				ScholarNodePrimaryLeaf newNodeL = new ScholarNodePrimaryLeaf(parent);
				ScholarNodePrimaryLeaf newNodeR = new ScholarNodePrimaryLeaf(parent);
				for (int i = 0; i<ScholarNode.order; i++){
					newNodeL.addPaper(i,Tayfun.paperAtIndex(i));
				}
				for (int j=ScholarNode.order, i=0; j<2*ScholarNode.order + 1; j++, i++){
					newNodeR.addPaper(i,Tayfun.paperAtIndex(j));
				}
				int a = 0;
				for (int i = 0; i < ((ScholarNodePrimaryIndex) parent).paperIdCount(); i++ ){
					ScholarNode tmpchild = ((ScholarNodePrimaryIndex) parent).getChildrenAt(i);
					if(tmpchild == Tayfun){
						a = i;
						break;
					}
				}
				((ScholarNodePrimaryIndex)parent).deleteChild(Tayfun);


				Integer copyUpValue = newNodeR.paperIdAtIndex(0);
				inserted = false;
				for (int i = 0; i<((ScholarNodePrimaryIndex)parent).paperIdCount(); i++){
					if (((ScholarNodePrimaryIndex)parent).paperIdAtIndex(i) > copyUpValue){
						((ScholarNodePrimaryIndex)parent).addPaperId(i,copyUpValue);
						((ScholarNodePrimaryIndex)parent).addChild(a,newNodeL);
						((ScholarNodePrimaryIndex)parent).addChild(a+1,newNodeR);
						inserted = true;
						break;
					}
				}
				if (!inserted){
					((ScholarNodePrimaryIndex)parent).addPaperId(copyUpValue);
					((ScholarNodePrimaryIndex)parent).addChild(newNodeL);
					((ScholarNodePrimaryIndex)parent).addChild(newNodeR);
				}
				//LEAF SPLİT ATTI
				//parent'ta split lazımsa
				ScholarNode grandParent;
				while(((ScholarNodePrimaryIndex)parent).paperIdCount() == 2*ScholarNode.order + 1){
					inserted = false;
					grandParent = parent.getParent();

					//parent root ve split lazım
					if (grandParent == null){
						ScholarNodePrimaryIndex newRoot = new ScholarNodePrimaryIndex(null);
						ScholarNodePrimaryIndex newInternalNodeL = new ScholarNodePrimaryIndex(newRoot);
						ScholarNodePrimaryIndex newInternalNodeR = new ScholarNodePrimaryIndex(newRoot);


						for (int i = 0; i<ScholarNode.order; i++){
							newInternalNodeL.addPaperId(i,((ScholarNodePrimaryIndex)parent).paperIdAtIndex(i));
							newInternalNodeL.addChild(((ScholarNodePrimaryIndex)parent).getChildrenAt(i));
							((ScholarNodePrimaryIndex)parent).getChildrenAt(i).setParent(newInternalNodeL);
						}
						newInternalNodeL.addChild(((ScholarNodePrimaryIndex)parent).getChildrenAt(ScholarNode.order));
						((ScholarNodePrimaryIndex)parent).getChildrenAt(ScholarNode.order).setParent(newInternalNodeL);


						for (int j=ScholarNode.order + 1, i=0; j<2*ScholarNode.order + 1; i++,j++){
							newInternalNodeR.addPaperId(i,((ScholarNodePrimaryIndex) parent).paperIdAtIndex(j));
							newInternalNodeR.addChild(((ScholarNodePrimaryIndex)parent).getChildrenAt(j));
							((ScholarNodePrimaryIndex)parent).getChildrenAt(j).setParent(newInternalNodeR);
						}
						newInternalNodeR.addChild(((ScholarNodePrimaryIndex)parent).getChildrenAt(2*ScholarNode.order+1));
						((ScholarNodePrimaryIndex)parent).getChildrenAt(2*ScholarNode.order + 1).setParent(newInternalNodeR);


						newRoot.addPaperId(((ScholarNodePrimaryIndex)parent).paperIdAtIndex(ScholarNode.order));
						newRoot.addChild(newInternalNodeL);
						newRoot.addChild(newInternalNodeR);
						primaryRoot = newRoot;
						break;
					}
					//parent internal ve split lazım
					else {
						ScholarNodePrimaryIndex newInternalNodeL = new ScholarNodePrimaryIndex(grandParent);
						ScholarNodePrimaryIndex newInternalNodeR = new ScholarNodePrimaryIndex(grandParent);
						for (int i = 0; i<ScholarNode.order; i++){
							newInternalNodeL.addPaperId(i,((ScholarNodePrimaryIndex) parent).paperIdAtIndex(i));
							newInternalNodeL.addChild(((ScholarNodePrimaryIndex)parent).getChildrenAt(i));
							((ScholarNodePrimaryIndex)parent).getChildrenAt(i).setParent(newInternalNodeL);
						}
						newInternalNodeL.addChild(((ScholarNodePrimaryIndex)parent).getChildrenAt(ScholarNode.order));
						((ScholarNodePrimaryIndex)parent).getChildrenAt(ScholarNode.order).setParent(newInternalNodeL);
						for (int j=ScholarNode.order + 1, i=0; j<2*ScholarNode.order + 1; i++,j++){
							newInternalNodeR.addPaperId(i,((ScholarNodePrimaryIndex) parent).paperIdAtIndex(j));
							newInternalNodeR.addChild(((ScholarNodePrimaryIndex)parent).getChildrenAt(j));
						}
						newInternalNodeR.addChild(((ScholarNodePrimaryIndex)parent).getChildrenAt(2*ScholarNode.order+1));
						((ScholarNodePrimaryIndex)parent).getChildrenAt(2*ScholarNode.order + 1).setParent(newInternalNodeR);

						Integer pushUpValue = ((ScholarNodePrimaryIndex)parent).paperIdAtIndex(ScholarNode.order);

						a = 0;
						for (int i = 0; i < ((ScholarNodePrimaryIndex) grandParent).paperIdCount(); i++ ){
							ScholarNode tmpchild = ((ScholarNodePrimaryIndex) grandParent).getChildrenAt(i);
							if(tmpchild == parent){
								a = i;
								break;
							}
						}
						((ScholarNodePrimaryIndex)grandParent).deleteChild(parent);
						for (int i = 0; i<((ScholarNodePrimaryIndex)grandParent).paperIdCount(); i++){
							if (((ScholarNodePrimaryIndex)grandParent).paperIdAtIndex(i) > pushUpValue){
								((ScholarNodePrimaryIndex)grandParent).addPaperId(i,pushUpValue);
								((ScholarNodePrimaryIndex)grandParent).addChild(a,newInternalNodeL);
								((ScholarNodePrimaryIndex)grandParent).addChild(a+1,newInternalNodeR);
								inserted = true;
								break;
							}
						}
						if (!inserted){
							((ScholarNodePrimaryIndex)grandParent).addPaperId(pushUpValue);
							((ScholarNodePrimaryIndex)grandParent).addChild(newInternalNodeL);
							((ScholarNodePrimaryIndex)grandParent).addChild(newInternalNodeR);
						}
					}
					parent = grandParent;
				}
			}
		}
		// SECONDARY B+ TREE
		// ROOT LEAF İSE
		if (secondaryRoot.getType() == ScholarNodeType.Leaf){
			ScholarNodeSecondaryLeaf Tayfun = (ScholarNodeSecondaryLeaf) secondaryRoot;
			int numberOfJournal = Tayfun.journalCount();
			//ROOT LEAF VE NO SPLİT
			boolean inserted = false;
			for (int i=0; i<numberOfJournal; i++){
				if (Tayfun.journalAtIndex(i).compareTo(paper.journal()) == 0){
					Tayfun.addPaper(i,paper);
					inserted = true;
					break;
				}
				else if (Tayfun.journalAtIndex(i).compareTo(paper.journal()) < 0){
					continue;
				} else{
					Tayfun.addPaper(i,paper);
					inserted = true;
					break;
				}
			}
			if (!inserted){
				Tayfun.addPaper(numberOfJournal,paper);
			}

			//ROOT LEAF VE SPLIT VAR
			if (Tayfun.journalCount() == 2*ScholarNode.order + 1){
				ScholarNodeSecondaryIndex newRoot = new ScholarNodeSecondaryIndex(null);
				ScholarNodeSecondaryLeaf newNodeL = new ScholarNodeSecondaryLeaf(newRoot);
				ScholarNodeSecondaryLeaf newNodeR = new ScholarNodeSecondaryLeaf(newRoot);
				for (int i = 0; i<ScholarNode.order; i++){
					ArrayList<Integer> temp = Tayfun.papersAtIndex(i);
					for (int j = 0; j<temp.size(); j++){
						CengPaper temp2 = new CengPaper(temp.get(j),"","", Tayfun.journalAtIndex(i));
						newNodeL.addPaper(i,temp2);
					}
				}

				for (int j=ScholarNode.order, i = 0; j<2*ScholarNode.order+1; j++, i++){
					ArrayList<Integer> temp = Tayfun.papersAtIndex(j);
					for (int k = 0; k<temp.size(); k++){
						CengPaper temp2 = new CengPaper(temp.get(k),"","", Tayfun.journalAtIndex(j));
						newNodeR.addPaper(i,temp2);
					}
				}
				newRoot.addJournal(newNodeR.journalAtIndex(0));
				newRoot.addChild(newNodeL);
				newRoot.addChild(newNodeR);
				secondaryRoot = newRoot;
			}
			// ROOT LEAF DEĞİL İSE
		} else {
			ScholarNode node = secondaryRoot;
			boolean x;
			while (node.getType() == ScholarNodeType.Internal){
				x = false;
				for (int i = 0; i<((ScholarNodeSecondaryIndex)node).journalCount(); i++){
					if (((ScholarNodeSecondaryIndex)node).journalAtIndex(i).compareTo(paper.journal()) > 0){
						node = ((ScholarNodeSecondaryIndex)node).getChildrenAt(i);
						x = true;
						break;
					}
				}
				if (!x){
					node = ((ScholarNodeSecondaryIndex)node).getChildrenAt(((ScholarNodeSecondaryIndex)node).journalCount());
				}
			}
			ScholarNodeSecondaryLeaf Tayfun = ((ScholarNodeSecondaryLeaf)node);


			//LEAF'TE SPLIT YOK
			boolean inserted = false;
			int numberOfJournal = Tayfun.journalCount();
			for (int i=0; i<numberOfJournal; i++){
				if (Tayfun.journalAtIndex(i).compareTo(paper.journal()) == 0){
					Tayfun.addPaper(i,paper);
					inserted = true;
					break;
				}
				else if (Tayfun.journalAtIndex(i).compareTo(paper.journal()) < 0){
					continue;
				} else{
					Tayfun.addPaper(i,paper);
					inserted = true;
					break;
				}
			}
			if (!inserted){
				Tayfun.addPaper(numberOfJournal,paper);
			}
			//LEAF'TE SPLIT VAR
			if (Tayfun.journalCount() == 2*ScholarNode.order + 1){
				ScholarNode parent = Tayfun.getParent();

				ScholarNodeSecondaryLeaf newNodeL = new ScholarNodeSecondaryLeaf(parent);
				ScholarNodeSecondaryLeaf newNodeR = new ScholarNodeSecondaryLeaf(parent);
				for (int i = 0; i<ScholarNode.order; i++){
					ArrayList<Integer> temp = Tayfun.papersAtIndex(i);
					for (int j = 0; j<temp.size(); j++){
						CengPaper temp2 = new CengPaper(temp.get(j),"","", Tayfun.journalAtIndex(i));
						newNodeL.addPaper(i,temp2);
					}
				}

				for (int j=ScholarNode.order, i = 0; j<2*ScholarNode.order+1; j++, i++){
					ArrayList<Integer> temp = Tayfun.papersAtIndex(j);
					for (int k = 0; k<temp.size(); k++){
						CengPaper temp2 = new CengPaper(temp.get(k),"","", Tayfun.journalAtIndex(j));
						newNodeR.addPaper(i,temp2);
					}
				}
				//TAYFUNUN INDEXI BUL

				int a = 0;
				for (int i = 0; i < ((ScholarNodeSecondaryIndex) parent).journalCount(); i++ ){
					ScholarNode tmpchild = ((ScholarNodeSecondaryIndex) parent).getChildrenAt(i);
					if(tmpchild == Tayfun){
						a = i;
						break;
					}
				}
				((ScholarNodeSecondaryIndex)parent).deleteChild(Tayfun);

				String copyUpValue = newNodeR.journalAtIndex(0);
				inserted = false;

				for (int i = 0; i<((ScholarNodeSecondaryIndex)parent).journalCount(); i++){
					if (((ScholarNodeSecondaryIndex)parent).journalAtIndex(i).compareTo(copyUpValue) > 0){
						((ScholarNodeSecondaryIndex)parent).addJournal(i,copyUpValue);
						((ScholarNodeSecondaryIndex)parent).addChild(a,newNodeL);
						((ScholarNodeSecondaryIndex)parent).addChild(a+1,newNodeR);
						inserted = true;
						break;
					}
				}
				if (!inserted){
					((ScholarNodeSecondaryIndex)parent).addJournal(copyUpValue);
					((ScholarNodeSecondaryIndex)parent).addChild(newNodeL);
					((ScholarNodeSecondaryIndex)parent).addChild(newNodeR);
				}
				// leaf split attı
				// parent split lazımsa
				ScholarNode grandParent;
				while (((ScholarNodeSecondaryIndex)parent).journalCount() == 2*ScholarNode.order + 1){
					inserted = false;
					grandParent = parent.getParent();

					if (grandParent == null){
						ScholarNodeSecondaryIndex newRoot = new ScholarNodeSecondaryIndex(null);
						ScholarNodeSecondaryIndex newInternalNodeL = new ScholarNodeSecondaryIndex(newRoot);
						ScholarNodeSecondaryIndex newInternalNodeR = new ScholarNodeSecondaryIndex(newRoot);

						for (int i = 0; i<ScholarNode.order; i++){
							newInternalNodeL.addJournal(i,((ScholarNodeSecondaryIndex)parent).journalAtIndex(i));
							newInternalNodeL.addChild(((ScholarNodeSecondaryIndex)parent).getChildrenAt(i));
							((ScholarNodeSecondaryIndex)parent).getChildrenAt(i).setParent(newInternalNodeL);
						}
						newInternalNodeL.addChild(((ScholarNodeSecondaryIndex)parent).getChildrenAt(ScholarNode.order));
						((ScholarNodeSecondaryIndex)parent).getChildrenAt(ScholarNode.order).setParent(newInternalNodeL);

						for (int j=ScholarNode.order + 1, i=0; j<2*ScholarNode.order + 1; i++,j++){
							newInternalNodeR.addJournal(i,((ScholarNodeSecondaryIndex) parent).journalAtIndex(j));
							newInternalNodeR.addChild(((ScholarNodeSecondaryIndex)parent).getChildrenAt(j));
							((ScholarNodeSecondaryIndex)parent).getChildrenAt(j).setParent(newInternalNodeR);
						}
						newInternalNodeR.addChild(((ScholarNodeSecondaryIndex)parent).getChildrenAt(2*ScholarNode.order+1));
						((ScholarNodeSecondaryIndex)parent).getChildrenAt(2*ScholarNode.order + 1).setParent(newInternalNodeR);

						newRoot.addJournal(((ScholarNodeSecondaryIndex)parent).journalAtIndex(ScholarNode.order));
						newRoot.addChild(newInternalNodeL);
						newRoot.addChild(newInternalNodeR);
						secondaryRoot = newRoot;
						break;
					}
					// parent internal ve split lazım
					else {
						ScholarNodeSecondaryIndex newInternalNodeL = new ScholarNodeSecondaryIndex(grandParent);
						ScholarNodeSecondaryIndex newInternalNodeR = new ScholarNodeSecondaryIndex(grandParent);
						for (int i = 0; i<ScholarNode.order; i++){
							newInternalNodeL.addJournal(i,((ScholarNodeSecondaryIndex) parent).journalAtIndex(i));
							newInternalNodeL.addChild(((ScholarNodeSecondaryIndex)parent).getChildrenAt(i));
							((ScholarNodeSecondaryIndex)parent).getChildrenAt(i).setParent(newInternalNodeL);
						}
						newInternalNodeL.addChild(((ScholarNodeSecondaryIndex)parent).getChildrenAt(ScholarNode.order));
						((ScholarNodeSecondaryIndex)parent).getChildrenAt(ScholarNode.order).setParent(newInternalNodeL);
						for (int j=ScholarNode.order + 1, i=0; j<2*ScholarNode.order + 1; i++,j++){
							newInternalNodeR.addJournal(i,((ScholarNodeSecondaryIndex) parent).journalAtIndex(j));
							newInternalNodeR.addChild(((ScholarNodeSecondaryIndex)parent).getChildrenAt(j));
						}
						newInternalNodeR.addChild(((ScholarNodeSecondaryIndex)parent).getChildrenAt(2*ScholarNode.order+1));
						((ScholarNodeSecondaryIndex)parent).getChildrenAt(2*ScholarNode.order + 1).setParent(newInternalNodeR);

						String pushUpValue = ((ScholarNodeSecondaryIndex)parent).journalAtIndex(ScholarNode.order);

						a = 0;
						for (int i = 0; i < ((ScholarNodeSecondaryIndex) grandParent).journalCount(); i++ ){
							ScholarNode tmpchild = ((ScholarNodeSecondaryIndex) grandParent).getChildrenAt(i);
							if(tmpchild == parent){
								a = i;
								break;
							}
						}
						((ScholarNodeSecondaryIndex)grandParent).deleteChild(parent);
						for (int i = 0; i<((ScholarNodeSecondaryIndex)grandParent).journalCount(); i++){
							if (((ScholarNodeSecondaryIndex)grandParent).journalAtIndex(i).compareTo(pushUpValue) > 0){
								((ScholarNodeSecondaryIndex)grandParent).addJournal(i,pushUpValue);
								((ScholarNodeSecondaryIndex)grandParent).addChild(a,newInternalNodeL);
								((ScholarNodeSecondaryIndex)grandParent).addChild(a+1,newInternalNodeR);
								inserted = true;
								break;
							}
						}
						if (!inserted){
							((ScholarNodeSecondaryIndex)grandParent).addJournal(pushUpValue);
							((ScholarNodeSecondaryIndex)grandParent).addChild(newInternalNodeL);
							((ScholarNodeSecondaryIndex)grandParent).addChild(newInternalNodeR);
						}

					}
					parent = grandParent;
				}
			}

		}
		return;
	}

	public CengPaper searchPaper(Integer paperId) {
		// TODO: Implement this method
		// find the paper with the searched paperId in primary B+ tree
		// return value will not be tested, just print according to the specifications
		ScholarNode node = primaryRoot;
		boolean x;
		int level = 0;
		while (node.getType() == ScholarNodeType.Internal){
			x = false;
			for (int m=0; m<level; m++){ System.out.print("\t"); }
			System.out.print("<index>\n");
			for (int i = 0; i<((ScholarNodePrimaryIndex)node).paperIdCount(); i++){
				for (int m=0; m<level; m++){ System.out.print("\t"); }
				System.out.print(((ScholarNodePrimaryIndex)node).paperIdAtIndex(i) + System.lineSeparator());
				//if (((ScholarNodePrimaryIndex)node).paperIdAtIndex(i) > paperId){
				//	node = ((ScholarNodePrimaryIndex)node).getChildrenAt(i);
				//	x = true;
				//	break;
				//}
			}
			for (int i = 0; i<((ScholarNodePrimaryIndex)node).paperIdCount(); i++){
				if (((ScholarNodePrimaryIndex)node).paperIdAtIndex(i) > paperId){
					node = ((ScholarNodePrimaryIndex)node).getChildrenAt(i);
					x = true;
					break;
				}
			}
			if (!x){
				node = ((ScholarNodePrimaryIndex)node).getChildrenAt(((ScholarNodePrimaryIndex)node).paperIdCount());
			}
			for (int m=0; m<level; m++){ System.out.print("\t"); }
			System.out.print("</index>\n");
			level++;
		}

		boolean find = false;
		ScholarNodePrimaryLeaf tayfun = (ScholarNodePrimaryLeaf) node;
		for (int k = 0; k<tayfun.paperCount(); k++){
			if ( tayfun.paperIdAtIndex(k)== paperId){
				CengPaper temp = tayfun.paperAtIndex(k);
				int paperIDPrint = temp.paperId();
				String journalPrint = temp.journal();
				String paperNamePrint = temp.paperName();
				String authorPrint = temp.author();
				find = true;
				for (int m=0; m<level; m++){ System.out.print("\t"); }
				System.out.print("<data>\n");
				for (int m=0; m<level; m++){ System.out.print("\t"); }
				System.out.print("<record>" + paperIDPrint + "|" +journalPrint + "|" +paperNamePrint + "|" +authorPrint + "</record>" +"\n" );
				for (int m=0; m<level; m++){ System.out.print("\t"); }
				System.out.print("</data>\n");
				return temp;
			}
		}
		if (!find){
			/*
			for (int m=0; m<level; m++){ System.out.print("\t"); }
			System.out.print("<data>\n");
			for (int l = 0; l<tayfun.paperCount(); l++){
				CengPaper temp = tayfun.paperAtIndex(l);
				int paperIDPrint = temp.paperId();
				String journalPrint = temp.journal();
				String paperNamePrint = temp.paperName();
				String authorPrint = temp.author();
				for (int m=0; m<level; m++){ System.out.print("\t"); }
				System.out.print("<record>" + paperIDPrint + "|" +journalPrint + "|" +paperNamePrint + "|" +authorPrint + "</record>" + "\n" );
			}
			for (int m=0; m<level; m++){ System.out.print("\t"); }
			System.out.print("</data>\n");
			 */
			System.out.print("Could not find " + paperId + "\n");
			return null;
		}
		return null;
	}

	public void searchJournal(String journal) {
		// TODO: Implement this method
		// find the journal with the searched journal in secondary B+ tree
		ScholarNode node = secondaryRoot;
		boolean x = false;
		int level = 0;
		while (node.getType() == ScholarNodeType.Internal){
			x = false;
			for (int m=0; m<level; m++){ System.out.print("\t"); }
			System.out.print("<index>\n");
			for (int i = 0; i<((ScholarNodeSecondaryIndex)node).journalCount(); i++){
				for (int m=0; m<level; m++){ System.out.print("\t"); }
				System.out.print(((ScholarNodeSecondaryIndex)node).journalAtIndex(i) + System.lineSeparator());
			}
			for (int i = 0; i<((ScholarNodeSecondaryIndex)node).journalCount(); i++){
				if (((ScholarNodeSecondaryIndex)node).journalAtIndex(i).compareTo(journal) > 0){
					node = ((ScholarNodeSecondaryIndex)node).getChildrenAt(i);
					x = true;
					break;
				}
			}
			if (!x){
				node = ((ScholarNodeSecondaryIndex)node).getChildrenAt(((ScholarNodeSecondaryIndex)node).journalCount());
			}
			for (int m=0; m<level; m++){ System.out.print("\t"); }
			System.out.print("</index>\n");
			level++;
		}
		boolean find = false;
		ScholarNodeSecondaryLeaf tayfun = (ScholarNodeSecondaryLeaf) node;
		for (int k = 0; k<tayfun.journalCount(); k++){

			if ( tayfun.journalAtIndex(k).equals(journal)){

				for (int m=0; m<level; m++){ System.out.print("\t"); }
				System.out.print("<data>\n");
				for (int m=0; m<level; m++){ System.out.print("\t"); }
				System.out.print(journal + System.lineSeparator());
				level++;

				ArrayList<Integer> temp = tayfun.papersAtIndex(k);
				for (int j = 0; j < temp.size(); j++){
					int paperIDPrint = temp.get(j);


					ScholarNode node2 = primaryRoot;
					boolean x2;
					while(node2.getType() == ScholarNodeType.Internal){
						x2 = false;
						for (int i=0; i<((ScholarNodePrimaryIndex)node2).paperIdCount(); i++){
							if (((ScholarNodePrimaryIndex)node2).paperIdAtIndex(i) > paperIDPrint){
								node2 = ((ScholarNodePrimaryIndex)node2).getChildrenAt(i);
								x2 = true;
								break;
							}
						}
						if (!x2){
							node2 = ((ScholarNodePrimaryIndex)node2).getChildrenAt(((ScholarNodePrimaryIndex)node2).paperIdCount());
						}
					}
					ScholarNodePrimaryLeaf Tayfun2 = ((ScholarNodePrimaryLeaf) node2);
					int f = 0;
					for (int s = 0; s < Tayfun2.paperCount(); s++){
						if (Tayfun2.paperAtIndex(s).paperId() == paperIDPrint){
							f = s;
							break;
						}
					}
					CengPaper tmp2 = Tayfun2.paperAtIndex(f);
					String journalPrint = tmp2.journal();
					String paperNamePrint = tmp2.paperName();
					String authorPrint = tmp2.author();

					for (int m=0; m<level; m++){ System.out.print("\t"); }
					System.out.print("<record>" + paperIDPrint + "|" + journalPrint + "|" + paperNamePrint + "|" + authorPrint + "</record>" + "\n" );
					find = true;
				}
				level--;
				for (int m=0; m<level; m++){ System.out.print("\t"); }
				System.out.print("</data>\n");
			}

		}
		if (!find){
			/*
			for (int m=0; m<level; m++){ System.out.print("\t"); }

			System.out.print("<data>\n");
			for (int l=0; l<tayfun.journalCount(); l++){
				for (int m=0; m<level; m++){ System.out.print("\t"); }
				System.out.print(tayfun.journalAtIndex(l) + System.lineSeparator());
				level++;
				ArrayList<Integer> temp = tayfun.papersAtIndex(l);
				for (int j = 0; j < temp.size(); j++){
					CengPaper tmp2 = new CengPaper(temp.get(j),"","", tayfun.journalAtIndex(l));
					int paperIDPrint = tmp2.paperId();
					//String journalPrint = tmp2.journal();
					//String paperNamePrint = tmp2.paperName();
					//String authorPrint = tmp2.author();
					for (int m=0; m<level; m++){ System.out.print("\t"); }
					System.out.print("<record>" + paperIDPrint + "|" + "</record>" + "\n" );
				}
				level--;
			}
			for (int m=0; m<level; m++){ System.out.print("\t"); }
			System.out.print("</data>\n");*/
			System.out.print("Could not find " + journal + "\n");
		}
		return;
	}

	public void printPrimaryScholar() {
		// TODO: Implement this method
		// print the primary B+ tree in Depth-first order
		ScholarNode node = primaryRoot;
		int level = 0;
		printPrimaryHelper(node, level);
		return;
	}

	public void printSecondaryScholar() {
		// TODO: Implement this method
		// print the secondary B+ tree in Depth-first order
		ScholarNode node = secondaryRoot;
		int level = 0;
		printSecondaryHelper(node, level);
		return;
	}

	// Extra functions if needed
	public void printPrimaryHelper (ScholarNode node, int level) {
		if (node.getType() == ScholarNodeType.Internal){
			for (int m=0; m<level; m++){ System.out.print("\t"); }
			System.out.print("<index>\n");
			for (int i = 0; i < ((ScholarNodePrimaryIndex)node).paperIdCount() ; i++){
				for (int m=0; m<level; m++){ System.out.print("\t"); }
				System.out.print(((ScholarNodePrimaryIndex)node).paperIdAtIndex(i) + System.lineSeparator());
			}
			for (int m=0; m<level; m++){ System.out.print("\t"); }
			System.out.print("</index>\n");
			for (int i = 0; i < ((ScholarNodePrimaryIndex)node).paperIdCount() + 1 ; i++){
				printPrimaryHelper(((ScholarNodePrimaryIndex)node).getChildrenAt(i),level+1);
			}
		}
		else if (node.getType() == ScholarNodeType.Leaf){
			for (int m=0; m<level; m++){ System.out.print("\t"); }
			System.out.print("<data>\n");
			for (int i = 0; i < ((ScholarNodePrimaryLeaf)node).paperCount(); i++){
				CengPaper temp = ((ScholarNodePrimaryLeaf)node).paperAtIndex(i);
				int paperIDPrint = temp.paperId();
				String journalPrint = temp.journal();
				String paperNamePrint = temp.paperName();
				String authorPrint = temp.author();
				for (int m=0; m<level; m++){ System.out.print("\t"); }
				System.out.print("<record>" + paperIDPrint + "|" +journalPrint + "|" +paperNamePrint + "|" +authorPrint + "</record>" +"\n" );
			}
			for (int m = 0; m<level; m++){ System.out.print("\t"); }
			System.out.print("</data>\n");
		}
		return;
	}
	public void printSecondaryHelper (ScholarNode node, int level) {
		if (node.getType() == ScholarNodeType.Internal){
			for (int m=0; m<level; m++){ System.out.print("\t"); }
			System.out.print("<index>\n");
			for (int i = 0; i < ((ScholarNodeSecondaryIndex)node).journalCount() ; i++){
				for (int m=0; m<level; m++){ System.out.print("\t"); }
				System.out.print(((ScholarNodeSecondaryIndex)node).journalAtIndex(i) + System.lineSeparator());
			}
			for (int m=0; m<level; m++){ System.out.print("\t"); }
			System.out.print("</index>\n");
			for (int i = 0; i < ((ScholarNodeSecondaryIndex)node).journalCount() + 1 ; i++){
				printSecondaryHelper(((ScholarNodeSecondaryIndex)node).getChildrenAt(i),level+1);
			}
		}
		else if (node.getType() == ScholarNodeType.Leaf){
			for (int m=0; m<level; m++){ System.out.print("\t"); }
			System.out.print("<data>\n");
			for (int i = 0; i < ((ScholarNodeSecondaryLeaf)node).journalCount(); i++){
				for (int m=0; m<level; m++){ System.out.print("\t"); }
				System.out.print(((ScholarNodeSecondaryLeaf)node).journalAtIndex(i) + System.lineSeparator());
				level++;

				ArrayList<Integer> temp = ((ScholarNodeSecondaryLeaf)node).papersAtIndex(i);
				for (int j = 0; j < temp.size(); j++){
					CengPaper tmp2 = new CengPaper(temp.get(j),"","", ((ScholarNodeSecondaryLeaf)node).journalAtIndex(i));
					int paperIDPrint = tmp2.paperId();
					//String journalPrint = tmp2.journal();
					//String paperNamePrint = tmp2.paperName();
					//String authorPrint = tmp2.author();

					for (int m=0; m<level; m++){ System.out.print("\t"); }
					System.out.print("<record>" + paperIDPrint + "</record>" + "\n");
				}
				level--;
			}
			for (int m=0; m<level; m++){ System.out.print("\t"); }
			System.out.print("</data>\n");
		}
		return;
	}
}


