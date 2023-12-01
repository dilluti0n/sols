# 6: Structures

[](https://github.com/dilluti0n/sols/tree/master/6)

solution for chap 6 exercises (1~6)

- `getword` : get next word or char from input
    - `int getword(char *word, int lim)`
        
        ```c
        int getword(char *word, int lim)
        {
        	int c, getch();
        	void ungetch();
        
        	while (isspace(c = getch()))
        		;
        	if (c != EOF)
        		*w++ = c;
        	if (!isalpha(c)) {
        		*w = '\0';
        		return c;
        	}
        	for (; --lim > 0; w++)
        		if (isalnum(*w = getch())) {
        			ungetch();
        			break;
        		}
        	*w = '\0';
        	return word[0];
        }
        ```
        
    
    input 의 각 단어를 space, 특수문자, 숫자로 구분하여 토큰화한다. 함수를 호출할 때마다 다음 토큰이 호출되며, input stream 이 마지막 토큰의 다음 글자로 넘겨진다. 각 
    
    - 특수문자
    - 알파벳으로 시작하지 않는 숫자
    - 알파벳으로 시작하는 연속된 알파벳 또는 숫자의 문자열
    
    은 하나의 토큰으로 취급된다. `Ex 6-1` 에서는 c언어에 적용하기 위해 `_` 로 시작하거나 중간에 `_` 가 있는 경우를 한 토큰으로 취급하고, `space` 를 skip 하는 앞 부분에 `literal`, `comment`, `preprocessor` 를 각각 구분해서 skip 하는 알고리즘을 추가해 주면 된다.
    
- Ex 6-1. `word_count.c`
    - `main`
        
        ```c
        main()
        {
        	int n;
        	char word[MAXWORD];
        
        	while (getword(word, MAXWORD) != EOF)
        		if (isalpha(word[0]))
        			if ((n = binsearch(word, keytab, NKEYS)) >= 0)
        				keytab[n].count++;
        	for (n = 0; n < NKEYS; n++)
        		if (keytab[n].count > 0)
        			printf ("%4d %s\n", keytab[n].count, keytab[n].word);
        	return 0;
        }
        ```
        

세야 하는 단어의 목록이 주어진 경우에는 위처럼 `array` 와 `binsearch` 를 사용해 효율적으로 단어를 셀 수 있지만, 그것이 주어지지 않은 경우에는 선형적으로 `array`에 대입해야 해 비효율적이며 적합하지 않다. `binary tree` 를 통해 효율적으로 단어를 세고, 알파벳 순으로 정렬하여 출력할 수 있다.

- `binary tree`
    
    ```c
    #include <stdio.h>
    #include <string.h>
    #include <stdlib.h>
    
    struct tnode {
    	char *word;
    	int count;
    	struct tnode *left;
    	struct tnode *right;
    };
    
    struct tnode *addtree(struct tnode *, char *);
    
    main()
    {
    	struct tnode *root = NULL;
    	/* ... */
    	while (getword(word, MAXWORD) != EOF)
    		root = addtree(root, word);
    	/* ... */
    	return 0;
    }
    
    struct tnode *addtree(struct tnode *p, char *w)
    {
    	int cond;
    
    	if (p == NULL) {
    		p = (struct tnode *) malloc(sizeof (struct tnode));
    		p->word = strdup(w);
    		p->count = 1;
    		p->left = p ->right = NULL;
    	} else if (!(cond = strcmp(p->word , w)) {
    		p->count++;
    	} else if (cond > 0) {
    		p->left = addtree(p->left, w);
    	} else {
    		p->right = addtree(p->right, w);
    	}
    	return p;
    }
    ```
    
- `treeprint`
    
    ```c
    void treeprint(struct tnode *p)
    {
    	if (p != NULL) {
    		treeprint(p->left);
    		printf("%s %d\n", p->word, p->count);
    		treeprint(p->right);
    	}
    }
    ```
    

`addtree` 는 재귀적으로 트리를 탐색하여 트리의 끝 부분에 노드를 추가하거나, 그 단어가 이미 트리에 있을 경우 `p->count`를 증가시켜 단어를 센다. 입력 `w` 를 각 노드에 저장된 단어 `p->word` 와 비교해 작을 경우에는 왼쪽 노드, 클 경우에는 오른쪽 노드로 탐색해 간다. `treeprint` 를 통해 각 노드를 알파벳 순으로 출력할 수 있다.

- Ex 6-2. `group.c`
    
    주어진 C 코드의 변수명을 찾아 변수명 앞 6글자(기본, 프로그램 arg로 입력받을 수 있음)가 같은 변수끼리 분류하고 각 그룹과 변수명을 알파벳순으로 출력한다. 이를 위해 이진 트리 아래 이진 트리가 있는 구조(즉, 상위 트리의 각 노드는 하위 트리의 root 의 포인터를 담고 있는 구조) 를 고안했다.
    
    - `trees in a tree`
        
        ```c
        	struct lower_node {
        	char *word;
        	struct lower_node *left;
        	struct lower_node *right;
        };
        
        struct upper_node {
        	struct lower_node *group_root;
        	struct upper_node *left;
        	struct upper_node *right;
        };
        
        struct upper_node *add_upper_tree(struct upper_node *p,
                                          char *w,
                                          int init_char)
        {
        	int cond;
        
        	if (p == NULL) {
        		p = (struct upper_node *) malloc(sizeof(struct upper_node));
        		p->group_root = add_lower_tree(p->group_root, w);
        		p->left = p->right = NULL;
        	} else if (!(cond = strncmp(p->word, w, init_char))) {
        		p->group_root = add_lower_tree(p->group_root, w);
        	} else if (cond > 0) {
        		p->left = add_upper_tree(p->left, w, init_char);
        	} else {
        		p->right = add_upper_tree(p->right, w, init_char);
        	}
        	return p;
        }
        
        struct lower_node *add_lower_tree(struct lower_node *p,
                                          char *w)
        {
        	int cond;
        
        	if (p == NULL) {
        		p = (struct lower_node *) malloc(sizeof(struct lower_node));
        		p->word = strdup(w);
        		p->left = p->right = NULL;
        	} else if ((cond = strcmp(p->word, w)) > 0) {
        		p->left = add_lower_tree(p->left, w);
        	} else if (cond < 0) {
        		p->right = add_lower_tree(p->right, w);
        	}
        	return p;
        }
        ```
        
    
    `add_lower_tree` 는 위 `addtree` 에서 `count` 를 뺀 함수고,  `add_upper_tree` 는 동일한 group 에 묶을 글자수 `init_char` 를 입력받아 `strncmp` 로 분류한 후, `add_lower_tree` 를 통해 `init_char` 만큼 동일한 변수명들을 같은 하위 트리에 넣는다.
    
    - `main`
        
        ```c
        int main(int argc, char **argv)
        {
        	int init_char = DEFAULT_INIT_CHAR; 
        	/* number of same initial char of vars to group_root */
        
        	struct upper_node *root = NULL;
        	char word[MAXWORD];
        
        	if ((init_char = parse_arg_list(argc, argv)) <= 0) {
        		fprintf(stderr, "err: invalid argument(s).\n");
        		fprintf(stderr, "useage: var_group [positive number]\n");
        		return EXIT_FAILURE;
        	}
        
        	while (get_w(word, MAXWORD) != EOF)
        		root = var_classify_and_load(word, root, init_char);
        	print_upper_tree(root);
        	return EXIT_SUCCESS;
        }
        ```
        
    
    한편 `parse_arg_list` 는 묶는 기준이 되는 앞 글자수를 입력받기위해 `argv, argc` 를 파싱하고, `var_classify_and_load` 는 입력받은 `word` 를 기반으로 하여, 프로그램에 선입력된 `data_types[]` 배열로 `binsearch` 를 하여 변수명을 특정한 뒤, `add_upper_tree` 를 통해 각 변수명을 트리에 그룹화해 저장한다. 변수명을 특정하려면 다음 단어를 읽는 등의 과정이 필요하므로, `getch-ungetch` 와 같이 버퍼화된 `getword` 인 `get_w-ungetw` 를 사용한다.
    
    꽤 많은 함수가 사용되었는데, 상위 함수(`main` 에 쓰이는 함수) 를 먼저 적고 각 함수에 사용 되어지는 하위 함수를 쓰는 순서를 지키면 가독성에 도움이 된다. `main` 함수에는 세부적이고 긴 logic 대신에 `parse_arg_list` 나 `var_classify_and_load` 같은 래핑 함수를 사용하는 것이 가독성 측면에서 효과적이다.
    
- Ex 6-3. `cross-referencer.c`
    
    입력한 텍스트의 `linking_words` 를 제외한 모든 단어를 사용된 줄 번호를 포함해 알파벳순으로 출력한다. 각 단어는 위와 동일한 순서로 이진 트리에 저장되며 각 단어가 사용된 줄 번호는 트리의 각 `node->list_head` 가 가리키는 linked list 에 저장된다. 
    
    - `linked lists in a tree`
        
        ```c
        struct tree_node {
        	char *word;
        	struct list_node *list_head; /* 줄 번호 list */
        	struct tree_node *left;
        	struct tree_node *right;
        };
        struct list_node {
        	int line;
        	struct list_node *next;
        }
        ```
        
    - `getword`
        
        ```c
        int getword(char *word, int lim)
        {
        	static int line = 1;
        	/* ... */
        	while (isspace(c = getch()))
        		if (c == '\n')
        			line++;
        	if (c == EOF)
        		return c;
        	/* ... */
        	return line;
        }
        ```
        
    
    각 단어가 사용된 줄 번호를 입력받기 위해 `static int line;` 을 사용하여 단어를 가져올때 그 단어의 줄 번호를 반환하도록 `getword` 를 수정했다.
    
    - `main`
        
        ```c
        main()
        {
        	char word[MAXWORD];
        	int line;
        	struct tree_node *root = NULL;
        
        	while ((line = getword(word, MAXWORD)) != EOF)
        		if (isalpha(word[0]) && !islinkingword(word))
        			root = addtree(root, word, line);
        	tree_print(root);
        
        	exit(EXIT_SUCCESS);
        }
        ```
        
    
    `islinkingword` 는 `binsearch` 를 통해 입력받은 `word` 가 `linking_words[]` 에 있는지 아닌지 살피며 있으면 `1`, 없으면 `0` 을 반환하며, 이를 통해 `linking_words` 에 존재하지 않는 `word` 만 `addtree` 로 전달하여 이진 트리에 `load` 한다.
    
    - `addtree`
        
        ```c
        struct tree_node* addtree(struct tree_node* p, char* w, int line)
        {
        	int cond;
        
        	if (p == NULL) {
        		p = (struct tree_node *) malloc(sizeof (struct tree_node));
        		p->word = strdup(w);
        		p->list_head = addlist(p->list_head, line);
        		p->left = NULL;
        		p->right = NULL;
        	} else if ((cond = strcmp(w, p->word)) == 0) {
        		p->list_head = addlist(p->list_head, line);
        	} else if (cond < 0) {
        		p->left = addtree(p->left, w, line);
        	} else {
        		p->right = addtree(p->right, w, line);
        	}
        	return p;
        }
        ```
        
        `addtree` 는 트리를 탐색하며 새로운 단어나 똑같은 단어를 마주했을 때 `addlist` 를 통해 노드에 줄 번호를 저장하며 `word` 를 알파벳순으로 `load` 하는 방법은 위와 동일하다.
        
    - `addlist`
        
        ```c
        struct list_node* addlist(struct list_node* p, int line)
        {
        	if (p == NULL) {
        		p = (struct list_node *) malloc(sizeof (struct list_node));
        		p->line = line;
        		p->next = NULL;
        	} else {
        		p->next = addlist(p->next, line);
        	}
        	return p;
        }
        ```
        
        `addlist` 는 호출될 때마다 재귀적으로 `list` 의 `tail` 을 탐색하여 `line` 을 데이터로 가지는 새로운 노드를 덧붙힌다.
        
    
    `tree_print` 는 위와 동일한 방식으로 저장된 단어를 알파벳순으로 출력하지만, 출력 시 `list_print` 를 사용해 각 노드가 가리키는 linked list 또한 출력한다.
    
    - `tree_print`
        
        ```c
        void tree_print(struct tree_node *p)
        {
        	if (p != NULL) {
        		tree_print(p->left);
        		printf("%s: ", p->word);
        		list_print(p->list_head);
        		tree_print(p->right);
        	}
        }
        ```
        
    - `list_print`
        
        ```c
        void list_print(struct list_node *p)
        {
        	if (p != NULL && p->next == NULL) {
        		printf("%d", p->line);
        		list_print(p->next);
        	} else if (p != NULL) {
        		printf("%d, ", p->line);
        		list_print(p->next);
        	} else {
        		putchar('\n');
        	}
        }
        ```
        
    
    각 단어의 줄번호가 몇개 저장될지 `getword` 가 문서의 끝까지 읽을 때까지 알 수 없기 때문에, 이진 트리의 각 노드에 하위 array 보다 하위 linked list 를 사용하여 저장하는 것이 효율적이며 적합하다.
    
- Ex 6-4. `frequency.c`
    - `linked list` , `tree`
        
        ```c
        struct lnode {
        	char *word;
        	int count;
        	struct lnode *next;
        };
        
        struct tnode {
        	struct lnode *list_node;
        	struct tnode *left;
        	struct tnode *right;
        };
        ```
        
    
    입력된 모든 단어를 세고 빈도의 역순으로 나열해야 한다. 단어와 빈도수를 링크드 리스트에 저장하고 각 링크드 리스트의 노드를 빈도수를 기준으로 위상정렬하는 방법을 사용했다. 위상정렬을 통해 만들어진 각 이진 트리의 노드는 각 링크드 리스트의 노드의 데이터가 아니라 포인터를 저장한다.
    
    - `main`
        
        ```c
        main()
        {
        	char word[MAXWORD];
        	struct lnode *head = NULL;
        	struct tnode *root = NULL;
        
        	while (getword(word, MAXWORD) != EOF)
        		if (isalpha(word[0]) && (head = addlist(head, word)) == NULL) {
        			fprintf(stderr, "addlist: malloc failed\n");
        			exit(EXIT_FAILURE);
        		}
        
        	struct lnode *node = head;
        	while (node != NULL) {
        		if ((root = sort_by_count(root, node)) == NULL) {
        			fprintf(stderr, "sort_by_count: malloc failed\n");
        			exit(EXIT_FAILURE);
        		}
        		node = node->next;
        	}
        	tree_print_and_free(root);
        	exit(EXIT_SUCCESS);
        }
        ```
        
        `addlist` 를 통해 각 단어를 입력받는 동시에 빈도수를 세고, `sort_by_count` 를 통해 단어의 빈도수를 기준으로 링크드 리스트의 노드를 위상정렬한 이진 트리를 생성한 뒤, `tree_print_and_free` 를 통해 출력과 동시에  `alloc` 한 메모리를 순차적으로 `free` 한다. 
        
        어차피 프로세스가 종료되면 OS가 자동으로 프로세스가 점유하던 메모리를 `free` 해 주며, 이 경우 `print` 하고 바로 종료되므로 굳이 `free` 할 필요가 없지만, 연습 삼아 해 봤다. 만일 이것보다 더 큰 프로그램을 만든다면 각 자료구조가 사용하는 메모리는 자료구조가 프로세스에서 더 쓰일 일이 없을 때 즉각적으로 `free` 해줘야 한다. 만일 프로세스 중 `alloc` 한 메모리 주소를 `free` 하지 않고 그 주소를 가리키는 포인터를 초기화하거나 한다면, (이 경우, `addlist` 는 노드를 `allocate` 한 뒤 `노드->word` 가 사용할 공간을 `strdup` 로 `allocate` 하는데, 그 노드의 부모 노드나 노드 자신을 노드 자신이나 `노드->word` 를 `free` 하지 않은 상태로 `free` 한 경우.) 심각한 문제가 발생하므로 메모리 관리에는 꼭 주의를 기울이자.
        
        단어가 아주 많다면, 단어 빈도수를 세고 입력받을 때 링크드 리스트 대신 이진 트리를 사용하면 메모리를 조금 희생하는 대신에 더 빠른 속도를 얻을 수 있다. 또는 링크드 리스트에 입력받은 자료를 배열로 옮겨 qsort 를 사용하는 방법을 생각해볼 수도 있지만, 속도는 비슷하거나 더 느릴 것 같다.
        
    

C 컴파일러는 `#define name defn` 과 같은 preprocessor macro 를 다룰 때, `name` 과 `defn` 을 `table` 에 등록시켜 놓고, 파일을 읽는 와중에 계속해서 `word` 를 `lookup` 하여 해당 `name` 이 `table` 에 존재할 때 이를 `defn` 로 대치시킨다. 이는 위의 `array` 나 `linked list` , `binary tree` 로도 구현할 수 있으나, 매 `word` 를 읽을 때마다 `lookup` 해야 하므로 그렇게 구현하면 컴파일러가 매우 매우 느려질 것이다. 

빠른 `lookup` 을 위해 `hashed table` 을 사용한다.

- `hashed table`
    
    ```c
    #define HASHSIZE 101
    
    struct nlist {
    	char *name;
    	char *defn;
    	struct nlist *next;
    }; /* node of linked list of each hashed array element */
    
    struct nlist *hashtab[HASHSIZE]; /* 
                                      * each elements of hashed
                                      * table points the head  
                                      * of each linked list.
                                      */
    ```
    
- `hash` function
    
    ```c
    /* hash: form hash for string s */
    unsigned hash(char *s)
    {
    	unsigned hashval;
    
    	for (hashval = 0; *s != '\0'; s++)
    		hashval = *s + 31 * hashval;
    	return hashval % HASHSIZE;
    }
    ```
    

즉, 특정 길이의 `array` , `hashtab[HASHSIZE]` 을 선언하고, `word` 를  `HASHSIZE`이하의 `hashval` 로 바꾸어 `hashtab[hashval]` 위치에 저장하는 것이다. 

- `install`
    
    ```c
    /* install: put (name, defn) in hashtab */
    struct nlist *install(char *name, char *defn)
    {
    	struct nlist *np;
    	unsigned hashval;
    
    	if ((np = lookup(name)) == NULL) { /* not found */
    		np = (struct nlist *) malloc(sizeof (*np));
    		if (np == NULL || (np->name = strdup(name)) == NULL)
    			return NULL;
    		hashval = hash(name);
    		np->next = hashtab[hashval];
    		hashtab[hashval] = np; /* insert np to head of list */
    	} else { /* found */
    		free((void *) np->defn); /* free previous defn */
    	}
    	if ((np->defn = strdup(defn)) == NULL)
    		return NULL;
    	return np;
    }
    ```
    

당연히 다른 단어라도 같은 `hash` 를 가지는 경우가 존재하니, `array` 의 구성요소는 `linked list` 의 `head` 를 가리키는 포인터로 하여 같은 `hash` 를 가지는 다른 단어의 경우 그 `hash` 의 `linked list` 에 추가되도록 하자.

- `lookup`
    
    ```c
    /* lookup: look for s in hashtab */
    struct nlist *lookup(char *s)
    {
    	struct nlist *np;
    
    	for (np = hashtab[hash(s)]; np != NULL; np = np->next)
    		if (!strcmp(s, np->name))
    			return np; /* found */
    	return NULL; /* not found */
    }
    ```
    

`hashed table` 을 사용하면 추가적인 메모리가 필요하고 `binary tree` 를 사용했을 때처럼 정렬은 불가능하지만, `lookup` 속도를 효과적으로 줄일 수 있다.

- Ex 6-5. `undef.c`
    
    `name` 이 입력되었을 때 이를 `table` 에서 제거한다. 당연히, `undef` 이후에도 `install` 과 `lookup` 은 사용할 수 있어야 한다.
    
    - `undef`
        
        ```c
        /* undef: remove node named (s) from table. return negative if failed. */
        int undef(char *s)
        {
        	struct nlist *node = hashtab[hash(s)];
        	struct nlist *prev = NULL;
        
        	for (; node != NULL; prev = node, node = node->next)
        		if (!strcmp(node->name, s)) {
        			if (prev != NULL)
        				prev->next = node->next;
        			else
        				hashtab[hash(s)] = node->next;
        			free(node->name);
        			free(node->defn);
        			free(node);
        			return 0;
        		}
        	return -1;
        }
        ```
        
    
    `linked list` 에서 노드를 제거하려면 이전 노드의 `next` 를 다음 노드로 바꾸면 된다. `head` 의 경우 `hashtab` 을 통해 접근할 수 있으므로 그것을 바꿔준다. `lookup` 은 이전 노드를 제공하지 않으므로 사용할 수 없다. 
    
    이 경우 삭제된 노드는 더이상 접근할 수 없으므로, 반드시 `allocate` 된 메모리는 `free` 해줘야 한다. 해주지 않으면 메모리 누수가 발생한다.
    
- Ex 6-6. `macro_processor.c`
    
    `hashed table` 을 이용해 매개변수를 제외한 C언어의 `#define` processor 을 구현해 보자. 
    
    - `main`
        
        ```c
        main()
        {
        	char syntax[MAXWORD];
        	int c;
        
        	while ((c = getword(syntax, MAXWORD)) != EOF)
        		if (c == '#' && preprocess() < 0)
        			return EXIT_FAILURE;
        	print_table();
        	return EXIT_SUCCESS;
        }
        ```
        
    
    `getword` 로 `c` 의 각 `syntax` 를 읽던 중 `#` 을 만나면 `preprocess` 를 실행시킨다.
    
    - `preprocess`
        
        ```c
        /* preprocessing unit */
        int preprocess(void)
        {
        	int err = 0;
        	char syntax[MAXWORD];
        	
        	getword(syntax, MAXWORD);
        	switch (syn_switcher_for_preprocess(syntax)) {
        	case DEFINE:
        		err = load_define_macro();
        		break;
        	case UNKNOWN:
        		fprintf(stderr, "%s: unknown prefix \"%s\".\n",__func__, syntax);
        		break;
        	}
        	return err;
        }
        ```
        
    
    `preprocess` 에서는 `#` 다음 단어인`syntax` 를 검사하며, `syntax` 가 `define` 인 경우`load_define_macro` 를 통해 그 줄의 macro 를 `hashtab` 에 load 한다. 만일 추후에 preprocess 를 위한 다른 `syntax` (`inlucde`, `pragma` ,…) 를 추가할 예정이라면, 여기에 쉽게 추가할 수 있다.
    
    - `load_define_macro`
        
        ```c
        /* get define macro (name, defn) from input stream and load to hashed list */
        int load_define_macro(void)
        {
        	char name[MAXWORD], defn[MAXWORD];
        	int err;
        
        	err = get_words_for_define_macro(name, defn, MAXWORD);
        	if (err >= 0 && install(name, defn) == NULL)
        		err = -1;
        	return err;
        }
        ```
        
    
    `load_define_macro` 는 `get_words_for_define_macro` 를 통해 그 줄의 `name` 과 `defn` 을 parse 하여 얻어오고, 그것을 그대로 `hashtab` 에 `install` 한다. 
    
    이때 `get_words_for_define_macro` 가 에러를 발생시킨다면(음수를 리턴한다면) `install` 하지 않고 음수를 리턴하며, `install` 에서 `allocation` 에러가 발생하면 `-1` 을 리턴한다.
    
    - `get_words_for_define_macro`
        
        ```c
        int get_words_for_define_macro(char *name, char *defn, int lim)
        {
        	int c;
        	char *w;
        
        	w = name; /* get name */
        	while (isspace(c = getch()))
        		;
        	if (c != EOF)
        		*w++ = c;
        	for (; w - name < lim; w++)
        		if (isspace(*w = c = getch())) {
        			ungetch(c);
        			break;
        		}
        	if (w - name >= lim) {
        		fprintf(stderr, "%s: too long macro name\n", __func__);
        		return -1;
        	}
        	*w = '\0'; /* name */
        	w = defn; /* get defn */
        	while (isblank(c = getch()))
        		;
        	if (c != EOF)
        		*w++ = c;
        	for (; w - defn < lim; w++)
        		if ((*w = c = getch()) == '\n') {
        			ungetch(c);
        			break;
        		}
        	if (w - defn >= lim) {
        		fprintf(stderr, "%s: too long defn for name: %s\n", __func__, name);
        		return -1;
        	}
        	*w = '\0'; /* defn */
        	return 0;
        }
        ```
        
    
     사이가 `space` 로 구분된 `name` 과 `defn` 을 각각 load 한다. 이때 주의점은 `defn` 은 중간에 `spcae` 가 들어가도 되므로, `\n` 이 발생할 때 까지 모든 문자를 load 해야 한다. 만일 적재할 문자가 너무 길면(`MAXWORD` 이상) 에러 메세지를 발생시키고 음수를 리턴한다.
    
    사용한 로직은 위에 다 주어져 있어 그리 어렵지 않았지만, 적절한 함수명과 범위를 정해 코드가 잘 구조화되고 잘 읽히도록 만드는 것이 어려웠다. 주어진 일을 잘 수행하도록 하는 코드를 구성하는 것은 함수명을 정하는 데에서부터 시작하는 것 같다. 혹은 막 쓰고 수정하면서 하던가…