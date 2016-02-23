#include "queryhandler.h"

QueryHandler::QueryHandler(IndexHandler* arg){
    Indexer = arg;
}

list<DocNode*>* QueryHandler::makeQuery(string arg){//needs to remove stems and then search for the query words.
    unordered_map<string,int>* stopWords = new unordered_map<string,int> ( {{"\n", 0}, {"able",  0},{"about",  0},{"above",  0},{"abroad",  0},{"according",  0},{"accordingly",  0},{"across",  0},{"actually",  0},{"adj",  0},{"after",  0},{"afterwards",  0},{"again",  0},{"against",  0},{"ago",  0},{"ahead",  0},{"ain\'t",  0},{"all",  0},{"allow",  0},{"allows",  0},{"almost",  0},{"alone",  0},{"along",  0},{"alongside",  0},{"already",  0},{"also",  0},{"although",  0},{"always",  0},{"am",  0},{"amid",  0},{"amidst",  0},{"among",  0},{"amongst",  0},{"an",  0},{"and",  0},{"another",  0},{"any",  0},{"anybody",  0},{"anyhow",  0},{"anyone",  0},{"anything",  0},{"anyway",  0},{"anyways",  0},{"anywhere",  0},{"apart",  0},{"appear",  0},{"appreciate",  0},{"appropriate",  0},{"are",  0},{"aren\'t",  0},{"around",  0},{"as",  0},{"a\'s",  0},{"aside",  0},{"ask",  0},{"asking",  0},{"associated",  0},{"at",  0},{"available",  0},{"away",  0},{"awfully",  0},{"back",  0},{"backward",  0},{"backwards",  0},{"be",  0},{"became",  0},{"because",  0},{"become",  0},{"becomes",  0},{"becoming",  0},{"been",  0},{"before",  0},{"beforehand",  0},{"begin",  0},{"behind",  0},{"being",  0},{"believe",  0},{"below",  0},{"beside",  0},{"besides",  0},{"best",  0},{"better",  0},{"between",  0},{"beyond",  0},{"both",  0},{"brief",  0},{"but",  0},{"by",  0},{"came",  0},{"can",  0},{"cannot",  0},{"cant",  0},{"can\'t",  0},{"caption",  0},{"cause",  0},{"causes",  0},{"certain",  0},{"certainly",  0},{"changes",  0},{"clearly",  0},{"c\'mon",  0},{"co",  0},{"co.",  0},{"com",  0},{"come",  0},{"comes",  0},{"concerning",  0},{"consequently",  0},{"consider",  0},{"considering",  0},{"contain",  0},{"containing",  0},{"contains",  0},{"corresponding",  0},{"could",  0},{"couldn\'t",  0},{"course",  0},{"c\'s",  0},{"currently",  0},{"dare",  0},{"daren\'t",  0},{"definitely",  0},{"described",  0},{"despite",  0},{"did",  0},{"didn\'t",  0},{"different",  0},{"directly",  0},{"do",  0},{"does",  0},{"doesn\'t",  0},{"doing",  0},{"done",  0},{"don\'t",  0},{"down",  0},{"downwards",  0},{"during",  0},{"each",  0},{"edu",  0},{"eg",  0},{"eight",  0},{"eighty",  0},{"either",  0},{"else",  0},{"elsewhere",  0},{"end",  0},{"ending",  0},{"enough",  0},{"entirely",  0},{"especially",  0},{"et",  0},{"etc",  0},{"even",  0},{"ever",  0},{"evermore",  0},{"every",  0},{"everybody",  0},{"everyone",  0},{"everything",  0},{"everywhere",  0},{"ex",  0},{"exactly",  0},{"example",  0},{"except",  0},{"fairly",  0},{"far",  0},{"farther",  0},{"few",  0},{"fewer",  0},{"fifth",  0},{"first",  0},{"five",  0},{"followed",  0},{"following",  0},{"follows",  0},{"for",  0},{"forever",  0},{"former",  0},{"formerly",  0},{"forth",  0},{"forward",  0},{"found",  0},{"four",  0},{"from",  0},{"further",  0},{"furthermore",  0},{"get",  0},{"gets",  0},{"getting",  0},{"given",  0},{"gives",  0},{"go",  0},{"goes",  0},{"going",  0},{"gone",  0},{"got",  0},{"gotten",  0},{"greetings",  0},{"had",  0},{"hadn\'t",  0},{"half",  0},{"happens",  0},{"hardly",  0},{"has",  0},{"hasn\'t",  0},{"have",  0},{"haven\'t",  0},{"having",  0},{"he",  0},{"he\'d",  0},{"he\'ll",  0},{"hello",  0},{"help",  0},{"hence",  0},{"her",  0},{"here",  0},{"hereafter",  0},{"hereby",  0},{"herein",  0},{"here\'s",  0},{"hereupon",  0},{"hers",  0},{"herself",  0},{"he\'s",  0},{"hi",  0},{"him",  0},{"himself",  0},{"his",  0},{"hither",  0},{"hopefully",  0},{"how",  0},{"howbeit",  0},{"however",  0},{"hundred",  0},{"i\'d",  0},{"ie",  0},{"if",  0},{"ignored",  0},{"i\'ll",  0},{"i\'m",  0},{"immediate",  0},{"in",  0},{"inasmuch",  0},{"inc",  0},{"inc.",  0},{"indeed",  0},{"indicate",  0},{"indicated",  0},{"indicates",  0},{"inner",  0},{"inside",  0},{"insofar",  0},{"instead",  0},{"into",  0},{"inward",  0},{"is",  0},{"isn\'t",  0},{"it",  0},{"it\'d",  0},{"it\'ll",  0},{"its",  0},{"it\'s",  0},{"itself",  0},{"i\'ve",  0},{"just",  0},{"k",  0},{"keep",  0},{"keeps",  0},{"kept",  0},{"know",  0},{"known",  0},{"knows",  0},{"last",  0},{"lately",  0},{"later",  0},{"latter",  0},{"latterly",  0},{"least",  0},{"less",  0},{"lest",  0},{"let",  0},{"let\'s",  0},{"like",  0},{"liked",  0},{"likely",  0},{"likewise",  0},{"little",  0},{"look",  0},{"looking",  0},{"looks",  0},{"low",  0},{"lower",  0},{"ltd",  0},{"made",  0},{"mainly",  0},{"make",  0},{"makes",  0},{"many",  0},{"may",  0},{"maybe",  0},{"mayn\'t",  0},{"me",  0},{"mean",  0},{"meantime",  0},{"meanwhile",  0},{"merely",  0},{"might",  0},{"mightn\'t",  0},{"mine",  0},{"minus",  0},{"miss",  0},{"more",  0},{"moreover",  0},{"most",  0},{"mostly",  0},{"mr",  0},{"mrs",  0},{"much",  0},{"must",  0},{"mustn\'t",  0},{"my",  0},{"myself",  0},{"name",  0},{"namely",  0},{"nd",  0},{"near",  0},{"nearly",  0},{"necessary",  0},{"need",  0},{"needn\'t",  0},{"needs",  0},{"neither",  0},{"never",  0},{"neverf",  0},{"neverless",  0},{"nevertheless",  0},{"new",  0},{"next",  0},{"nine",  0},{"ninety",  0},{"no",  0},{"nobody",  0},{"non",  0},{"none",  0},{"nonetheless",  0},{"noone",  0},{"no-one",  0},{"nor",  0},{"normally",  0},{"not",  0},{"nothing",  0},{"notwithstanding",  0},{"novel",  0},{"now",  0},{"nowhere",  0},{"obviously",  0},{"of",  0},{"off",  0},{"often",  0},{"oh",  0},{"ok",  0},{"okay",  0},{"old",  0},{"on",  0},{"once",  0},{"one",  0},{"ones",  0},{"one\'s",  0},{"only",  0},{"onto",  0},{"opposite",  0},{"or",  0},{"other",  0},{"others",  0},{"otherwise",  0},{"ought",  0},{"oughtn\'t",  0},{"our",  0},{"ours",  0},{"ourselves",  0},{"out",  0},{"outside",  0},{"over",  0},{"overall",  0},{"own",  0},{"particular",  0},{"particularly",  0},{"past",  0},{"per",  0},{"perhaps",  0},{"placed",  0},{"please",  0},{"plus",  0},{"possible",  0},{"presumably",  0},{"probably",  0},{"provided",  0},{"provides",  0},{"que",  0},{"quite",  0},{"qv",  0},{"rather",  0},{"rd",  0},{"re",  0},{"really",  0},{"reasonably",  0},{"recent",  0},{"recently",  0},{"regarding",  0},{"regardless",  0},{"regards",  0},{"relatively",  0},{"respectively",  0},{"right",  0},{"round",  0},{"said",  0},{"same",  0},{"saw",  0},{"say",  0},{"saying",  0},{"says",  0},{"second",  0},{"secondly",  0},{"see",  0},{"seeing",  0},{"seem",  0},{"seemed",  0},{"seeming",  0},{"seems",  0},{"seen",  0},{"self",  0},{"selves",  0},{"sensible",  0},{"sent",  0},{"serious",  0},{"seriously",  0},{"seven",  0},{"several",  0},{"shall",  0},{"shan\'t",  0},{"she",  0},{"she\'d",  0},{"she\'ll",  0},{"she\'s",  0},{"should",  0},{"shouldn\'t",  0},{"since",  0},{"six",  0},{"so",  0},{"some",  0},{"somebody",  0},{"someday",  0},{"somehow",  0},{"someone",  0},{"something",  0},{"sometime",  0},{"sometimes",  0},{"somewhat",  0},{"somewhere",  0},{"soon",  0},{"sorry",  0},{"specified",  0},{"specify",  0},{"specifying",  0},{"still",  0},{"sub",  0},{"such",  0},{"sup",  0},{"sure",  0},{"take",  0},{"taken",  0},{"taking",  0},{"tell",  0},{"tends",  0},{"th",  0},{"than",  0},{"thank",  0},{"thanks",  0},{"thanx",  0},{"that",  0},{"that\'ll",  0},{"thats",  0},{"that\'s",  0},{"that\'ve",  0},{"the",  0},{"their",  0},{"theirs",  0},{"them",  0},{"themselves",  0},{"then",  0},{"thence",  0},{"there",  0},{"thereafter",  0},{"thereby",  0},{"there\'d",  0},{"therefore",  0},{"therein",  0},{"there\'ll",  0},{"there\'re",  0},{"theres",  0},{"there\'s",  0},{"thereupon",  0},{"there\'ve",  0},{"these",  0},{"they",  0},{"they\'d",  0},{"they\'ll",  0},{"they\'re",  0},{"they\'ve",  0},{"thing",  0},{"things",  0},{"think",  0},{"third",  0},{"thirty",  0},{"this",  0},{"thorough",  0},{"thoroughly",  0},{"those",  0},{"though",  0},{"three",  0},{"through",  0},{"throughout",  0},{"thru",  0},{"thus",  0},{"till",  0},{"to",  0},{"together",  0},{"too",  0},{"took",  0},{"toward",  0},{"towards",  0},{"tried",  0},{"tries",  0},{"truly",  0},{"try",  0},{"trying",  0},{"t\'s",  0},{"twice",  0},{"two",  0},{"un",  0},{"under",  0},{"underneath",  0},{"undoing",  0},{"unfortunately",  0},{"unless",  0},{"unlike",  0},{"unlikely",  0},{"until",  0},{"unto",  0},{"up",  0},{"upon",  0},{"upwards",  0},{"us",  0},{"use",  0},{"used",  0},{"useful",  0},{"uses",  0},{"using",  0},{"usually",  0},{"v",  0},{"value",  0},{"various",  0},{"versus",  0},{"very",  0},{"via",  0},{"viz",  0},{"vs",  0},{"want",  0},{"wants",  0},{"was",  0},{"wasn\'t",  0},{"way",  0},{"we",  0},{"we\'d",  0},{"welcome",  0},{"well",  0},{"we\'ll",  0},{"went",  0},{"were",  0},{"we\'re",  0},{"weren\'t",  0},{"we\'ve",  0},{"what",  0},{"whatever",  0},{"what\'ll",  0},{"what\'s",  0},{"what\'ve",  0},{"when",  0},{"whence",  0},{"whenever",  0},{"where",  0},{"whereafter",  0},{"whereas",  0},{"whereby",  0},{"wherein",  0},{"where\'s",  0},{"whereupon",  0},{"wherever",  0},{"whether",  0},{"which",  0},{"whichever",  0},{"while",  0},{"whilst",  0},{"whither",  0},{"who",  0},{"who\'d",  0},{"whoever",  0},{"whole",  0},{"who\'ll",  0},{"whom",  0},{"whomever",  0},{"who\'s",  0},{"whose",  0},{"why",  0},{"will",  0},{"willing",  0},{"wish",  0},{"with",  0},{"within",  0},{"without",  0},{"wonder",  0},{"won\'t",  0},{"would",  0},{"wouldn\'t",  0},{"yes",  0},{"yet",  0},{"you",  0},{"you\'d",  0},{"you\'ll",  0},{"your",  0},{"you\'re",  0},{"yours",  0},{"yourself",  0},{"yourselves",  0},{"you\'ve",  0},{"zero", 0}} );
    string words;
    vector<list<DocNode*>*> lists;
    list<DocNode*>* notlist = NULL;
    list<DocNode*>* final = new list<DocNode*>;
    stringstream ss(arg);
    string sub;
    getline(ss, sub, ' ');
    if(!sub.compare("AND")){//AND case
        while(getline(ss, sub, ' ')){ //tokenize string
          if(!sub.compare("NOT")){
            getline(ss, sub, ' ');
            if(stopWords->count(sub) != 0){
                break;
            }
            transform(sub.begin(), sub.end(), sub.begin(), ::tolower);
            Porter2Stemmer::stem(sub);
            notlist = Indexer->search(sub);
            break;
          }
          transform(sub.begin(), sub.end(), sub.begin(), ::tolower);
          while(stopWords->count(sub) != 0){ //go to the next word if the word is a stopword
            getline(ss, sub, ' ');
          }
          Porter2Stemmer::stem(sub);
          lists.push_back(Indexer->search(sub));
          }




        // put the lists[0] into final
        list<DocNode*>::iterator finit = lists[0]->begin();
        while(finit != lists[0]->end()){
          final->push_back(*finit);
          finit++;
        }
        for(int i = 1; i < lists.size(); i++){
          list<DocNode*>::iterator it = final->begin();
          list<DocNode*>::iterator it1 = lists[i]->begin();
          while(it != final->end() && it1 != lists[i]->end()){ // loop until either are at end
            if(((*it)->getID() < (*it1)->getID())) {
              it = final->erase(it);
            }
            else if(((*it)->getID() > (*it1)->getID())){
              it1++;
            }
            else{
              (*it)->mergeNode(*it1);
              it++;
              it1++;
            }
          }
          while(it != final->end()){
            it = final->erase(it);
          }
        }
    }

    else if(!sub.compare("OR")){//OR case
        while(getline(ss, sub, ' ')){ //tokenize string
          if(!sub.compare("NOT")){
            getline(ss, sub, ' ');
            if(stopWords->count(sub) != 0){
                break;
            }
            transform(sub.begin(), sub.end(), sub.begin(), ::tolower);
            Porter2Stemmer::stem(sub);
            notlist = Indexer->search(sub);
            break;
          }
          transform(sub.begin(), sub.end(), sub.begin(), ::tolower);
          while(stopWords->count(sub) != 0){ //go to next word if the word is stopword
            getline(ss, sub, ' ');
          }
          Porter2Stemmer::stem(sub);
          lists.push_back(Indexer->search(sub));


        }
        // put the lists[0] into final
        list<DocNode*>::iterator finit = lists[0]->begin();
        while(finit != lists[0]->end()){
          final->push_back(*finit);
          finit++;
        }
        //merge for 1 to end
        for(unsigned int i = 1; i < lists.size(); i++){ //basically doing a merge sort with index 0 and i
            list<DocNode*>::iterator it = final->begin();//iterator for final
            list<DocNode*>::iterator it1 = lists[i]->begin();//iterator for current
            while((it != final->end()) && (it1 != lists[i]->end())){//loop until either at end
                if(((*it)->getID() < (*it1)->getID())){
                    it++;
                }
                else if(((*it)->getID() > (*it1)->getID())){
                    final->insert(it,*it1);
                    it1++;
                }
                else{
                    (*it)->mergeNode(*it1);
                    it++;
                    it1++;
                }
            }
            while(it1 != lists[i]->end()){
              final->push_back(*it1);
              it1++;
            }
            lists[0] = final;
        }
    }
    else{//regular case
      string thefinal = sub;
      if(stopWords->count(sub) != 0){ //if stopword then there is no query
      }
      else{//otherwise this is the query
        transform(sub.begin(), sub.end(), sub.begin(), ::tolower);
        Porter2Stemmer::stem(sub);
        list<DocNode*>*temp = (Indexer->search(sub));
        list<DocNode*>::iterator it = temp->begin();
        while(it != temp->end()){
          final->push_back(*it);
          it++;
        }
      }
      getline(ss, sub, ' ');
      if(!sub.compare("NOT")){
        getline(ss, sub, ' ');
        if(stopWords->count(sub) != 0){
        }
        else{
          transform(sub.begin(), sub.end(), sub.begin(), ::tolower);
          Porter2Stemmer::stem(sub);
          notlist = Indexer->search(sub);
          if(!thefinal.compare(sub)){
            final->clear();
            delete stopWords;
            return final;
          }
          goto mylabel;
        }
      }
    }
    if(lists.empty()){//if no queries to search return empty list
        delete stopWords;
        return final;
    }
    if(notlist == NULL){
      delete stopWords;
      return final;
    }
    mylabel:
    list<DocNode*>::iterator itf = final->begin();
    list<DocNode*>::iterator itn = notlist->begin();
    while(itn != notlist->end() && itf != final->end()){
        if((*itn)->getID() > (*itf)->getID()){
            itf++;
        }
        else if((*itn)->getID() < (*itf)->getID()){
          itn++;
        }
        else{
          itf = final->erase(itf);
          itn++;
        }
    }
    delete stopWords;
    return(final);
}
