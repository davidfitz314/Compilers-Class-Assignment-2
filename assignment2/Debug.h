#ifndef _DEBUG_H_
#define _DEBUG_H_

#define ShowMessages 0
#if ShowMessages
#define MSG(X) std::cout << X << std::endl;
#else
#define MSG(X) ;
#endif


#endif
