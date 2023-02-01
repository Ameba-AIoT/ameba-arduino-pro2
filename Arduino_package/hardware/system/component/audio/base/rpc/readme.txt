HOW TO use RPC procedure :


 (1) <编辑 Script 档>
     (Description) 编辑一个 script 文件，放在script文件夹中, 注意 program id 和 version id 要和别人不同!
                   示例参考  "AudioRPC_System.x",      
                   这是 Audio 的 AP (比如 KR4) 要送给 DSP 所需的 funciton 和 data structure
                   在 script 前几行, 可加入一些 .insert <...>
                   在 generate 出来的 .h 文件中, 就会有这几行 #include...
     (Example) 
            .insert <RPCBaseDS.h>
            struct AA {
              long sum;
              char t_char;
            }
            
            program ITest {
              version VERSION {
                 int VE_RPC_RequestWriteSpace(long)=1;
                 struct AA TestFunction(char)=2;
              }=0;
            }=0;
            
     (NOTE****) program ID 编号规则：0~100 给 RPC library 使用
                                     1000~1999 给 Media 使用
                                     2000~2999 给 Audio 使用
                                     3000~3999 给 Speech 使用
									 ....
  
 (2) <Run rpcgen 来产生 code>
     (Description) 目录在 component/audio/base/rpc/tools/rpcgen, 平台为 Linux
                   cd rpcgen/;  Makefile
                   执行 ./rpcgen AudioRPC_System.x
                   会产生 .h  _data.h  _svc.c _clnt.c _xdr.c 这五个文件案
  
 (3) <产生文件说明>
     (Description) _svc.c 放在被呼叫的那一端 (示例是 component/example/rpc)
                   _clnt.c 放在呼叫的那一端  (示例是 component/example/rpc)     
                   .h _data.h _xdr.c 这三个文件, 呼叫端和被呼叫端都需要放
     
 (4) <被呼叫端: 程式实作>
     (Desctiption) 编辑被呼叫的 function 文件 (示例是 component/example/rpc)
                   如果当初在 .x 内所定义的 function name 是 TEST_RPC_ToAgent_Create_0();
                   那被呼叫端相对应的 function name 就是 TEST_RPC_ToAgent_Create数字_svc();
     (NOTE***) 可使用 (2) 步骤来产生 template 文件
     (Example) 
			RPCRES_LONG *TEST_RPC_ToAgent_Create_0_svc(TEST_RPC_INSTANCE *pParam, RPC_STRUCT *pRpcStruct, RPCRES_LONG *pRes)
			{
				if (p_TEST_RPC_ToAgent_Create_0_svc) {
					p_TEST_RPC_ToAgent_Create_0_svc(pParam, pRpcStruct, pRes);
					return pRes;
				} else {
					return pRes;
				}
			}
 
 (5) <呼叫端：使用方法>
     (Desctiption) 呼叫前, 记得先使用 function: 
                   struct CLNT_STRUCT clnt = prepareCLNT(mode, PROGRAM NAME, VERSION NAME); 
                   其中 mode 有 BLOCK_MODE, NONBLOCK_MODE, USE_INTR_BUF, USE_POLL_BUF   
     
                   然后再呼叫 function:  
                        return参数 = TEST_RPC_ToAgent_Create_0(&自订参数, &clnt);
                   其中 clnt 是刚刚用 prepareCLNT(); 得到的结果
     (Example)
           int *result;
           long arg = 123;
        
           CLNT_STRUCT clnt = prepareCLNT(BLOCK_MODE | USE_POLL_BUF, ITest, Version);
           result = TEST_RPC_ToAgent_Create_0(&arg, &clnt);
        
           if (result) == (int *)-1)
               printf("function send error/n");
           else
               printf("function send success, return value: %d /n", *result);
                 
           free(result);     // NOTE*** 必须手动 free result !!!!!!!
 
 (6) <测试方法>
     (Desctiption) 以后 RPC alwayse listen 的 dispatch thread 可能会由 OS boot 起来的时候 run
                   但是现在必须我们手动加入
     
                   Unit_test (示例在 component/example/rpc/example_rpc.c)
                   需要呼叫 register function, 
                   把这个 program 注册进去 (示例是 TEST_AGENT_0_register();)
                   还要记得注册 reply handler (示例是 ReplyHandler_register();)
                   然后 create RPCProxy 的 Thread 来 listen... 

     (Example)
           struct REG_STRUCT * rnode = NULL;

           // 以下是 register function 们
           rnode = (struct REG_STRUCT *)TEST_AGENT_0_register(rnode);  // Client program 0
           rnode = (struct REG_STRUCT *)AUDIO_AGENT_0_register(rnode);  // Client program 1
           rnode = (struct REG_STRUCT *)ReplyHandler_register(rnode);  // Reply Handler    
           
           RPC_InitProxy(pReg, RPC_DIR_AP_NP); // 将 RPC listen 的 dispatch thread run 起来 ，
		   传入各个不同CPU 之间的通道ID
     
 (6) <audogen.sh脚本生成>
	 (Desctiption) 使用脚本audogen.sh 不带参数生成script下所有模块中的.x文件对应的所有文件，
					生成的文件放在rpc/generate下对应各个模块的文件夹中，带模块名称只生成单个模块
					对应的文件。
	 (Example)
			./autogen.sh 
			./autogen.sh audio