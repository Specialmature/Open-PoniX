/*
 *
 *  Copyright (C) 2007-2014 SimplyCore, LLC
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 *
 */

#include "usbd.h"
ssize_t IIllllIII(void*,const char __user*,size_t);ssize_t IIllIIlI(void*,char 
__user*,size_t);long IIlIlllIl(void*,unsigned int,unsigned long);long lIIIlllI(
void*,unsigned int,unsigned long);int IIlIlIlll(void*);int lllIIIll(void*);
unsigned int IIIllIlI(void*,struct file*,poll_table*lllIII);int lIIIIlll(struct 
llIll*IIlII,const char*IlIIl,size_t IlIII);int llIlllll(struct llIll*IIlII,const
 char*IlIIl,size_t IlIII);int IIIIlllll(struct llIll*IIlII,const char*IlIIl,
size_t IlIII);int lIllIlII(struct llIll*IIlII,const char*IlIIl,size_t IlIII);int
 IIIlIIllI(struct llIll*IIlII,const char*IlIIl,size_t IlIII);int lllIIlII(struct
 llIll*IIlII,const char*IlIIl,size_t IlIII);int lIIllIIlI(struct llIll*IIlII,
const char*IlIIl,size_t IlIII);int lIlIIllII(struct llIll*IIlII,const char*IlIIl
,size_t IlIII);int lIllllIIl(struct llIll*IIlII,const char*IlIIl,size_t IlIII);
struct llIll*IIlIllIl(void){struct llIll*lllll;lllll=kmalloc(sizeof(*lllll),
GFP_KERNEL);if(lllll){memset(lllll,(0x480+7942-0x2386),sizeof(*lllll));lllll->
ops.open=IIlIlIlll;lllll->ops.release=lllIIIll;lllll->ops.unlocked_ioctl=
IIlIlllIl;
#ifdef CONFIG_COMPAT
lllll->ops.compat_ioctl=lIIIlllI;
#endif
lllll->ops.read=IIllIIlI;lllll->ops.write=IIllllIII;lllll->ops.poll=IIIllIlI;
lllll->context=lllll;lllll->llIllI=IlIllIII();if(!lllll->llIllI){kfree(lllll);
lllll=NULL;}}return lllll;}void lllIlIlIl(struct llIll*lllll){if(lllll){if(lllll
->llIllI){llIlIIlI(lllll->llIllI);lllll->llIllI=NULL;}kfree(lllll);}}inline int 
lllIlIlI(struct llIll*lllll,const char*IllllI){return IIIlIIIll(lllll->llIllI,
IllllI,strlen(IllllI)+(0x4ab+4925-0x17e7),(0x35c+6877-0x1e39));}ssize_t IIllIIlI
(void*context,char __user*IlIIl,size_t IlIII){struct llIll*lllll=context;IIIll(
"\x75\x73\x62\x64\x5f\x6d\x63\x5f\x72\x65\x61\x64" "\n");return IIIIlIIlI(lllll
->llIllI,IlIIl,IlIII,(0xb28+2271-0x1406));}ssize_t IIllllIII(void*context,const 
char __user*IlIIl,size_t IlIII){struct llIll*IIlII=context;ssize_t lIlll=
(0x144b+610-0x16ad);char lllIIl[(0x65a+4463-0x1797)];IIIll(
"\x75\x73\x62\x64\x5f\x6d\x63\x5f\x77\x72\x69\x74\x65\x3a\x20\x2b\x2b" "\n");
IIIll(
"\x75\x73\x62\x64\x5f\x6d\x63\x5f\x77\x72\x69\x74\x65\x3a\x20\x42\x75\x66\x3d\x30\x78\x25\x70" "\n"
,IlIIl);do{if(IlIII>sizeof(lllIIl)){IIIll(
"\x75\x73\x62\x64\x5f\x6d\x63\x5f\x77\x72\x69\x74\x65\x3a\x20\x74\x6f\x6f\x20\x6c\x61\x72\x67\x65\x20\x77\x72\x69\x74\x65\x20\x72\x65\x71\x75\x65\x73\x74" "\n"
);lIlll=-EFAULT;break;}if(copy_from_user(lllIIl,IlIIl,IlIII)!=(0x1a5+3116-0xdd1)
){IIIll(
"\x75\x73\x62\x64\x5f\x6d\x63\x5f\x77\x72\x69\x74\x65\x3a\x20\x63\x61\x6e\x6e\x6f\x74\x20\x63\x6f\x70\x79\x20\x62\x75\x66\x66\x65\x72" "\n"
);lIlll=-EFAULT;break;}lllIIl[IlIII]=(0x89d+4038-0x1863);IIIll(
"\x75\x73\x62\x64\x5f\x6d\x63\x5f\x77\x72\x69\x74\x65\x3a\x20\x63\x6f\x6d\x6d\x61\x6e\x64\x20\x69\x73\x20" "\"" "\x25\x73" "\"\n"
,lllIIl);
#ifdef _USBD_ENABLE_STUB_
if(strnicmp(lllIIl,"\x73\x68\x61\x72\x65",(0x1149+2293-0x1a39))==
(0x1c75+1056-0x2095)){IIIll(
"\x75\x73\x62\x64\x5f\x6d\x63\x5f\x77\x72\x69\x74\x65\x3a\x20\x53\x48\x41\x52\x45\x20\x63\x6f\x6d\x6d\x61\x6e\x64\x20\x72\x65\x63\x65\x69\x76\x65\x64" "\n"
);lIlll=lIIIIlll(IIlII,lllIIl+(0x217+7302-0x1e98),IlIII-(0x8fa+2693-0x137a));}
else if(strnicmp(lllIIl,"\x75\x6e\x73\x68\x61\x72\x65",(0x358+7547-0x20cc))==
(0x692+6488-0x1fea)){IIIll(
"\x75\x73\x62\x64\x5f\x6d\x63\x5f\x77\x72\x69\x74\x65\x3a\x20\x55\x4e\x53\x48\x41\x52\x45\x20\x63\x6f\x6d\x6d\x61\x6e\x64\x20\x72\x65\x63\x65\x69\x76\x65\x64" "\n"
);lIlll=llIlllll(IIlII,lllIIl+(0x847+3979-0x17cb),IlIII-(0xf16+2893-0x1a5c));}
else if(strnicmp(lllIIl,"\x72\x65\x73\x65\x74",(0x6ea+4333-0x17d2))==
(0xf4f+1269-0x1444)){IIIll(
"\x75\x73\x62\x64\x5f\x6d\x63\x5f\x77\x72\x69\x74\x65\x3a\x20\x52\x45\x53\x45\x54\x20\x63\x6f\x6d\x6d\x61\x6e\x64\x20\x72\x65\x63\x65\x69\x76\x65\x64" "\n"
);lIlll=IIIlIIllI(IIlII,lllIIl+(0xabd+2177-0x1339),IlIII-(0x1435+208-0x1500));}
else if(strnicmp(lllIIl,"\x61\x64\x64\x65\x78\x63\x6c\x75\x64\x65",
(0x5c4+3570-0x13ac))==(0x1010+5345-0x24f1)){IIIll(
"\x75\x73\x62\x64\x5f\x6d\x63\x5f\x77\x72\x69\x74\x65\x3a\x20\x41\x44\x44\x45\x58\x43\x4c\x55\x44\x45\x20\x63\x6f\x6d\x6d\x61\x6e\x64\x20\x72\x65\x63\x65\x69\x76\x65\x64" "\n"
);lIlll=IIIIlllll(IIlII,lllIIl+(0xab2+1031-0xeaf),IlIII-(0x51+786-0x359));}else 
if(strnicmp(lllIIl,"\x72\x65\x6d\x65\x78\x63\x6c\x75\x64\x65",(0x20d+2765-0xcd0)
)==(0xa40+4237-0x1acd)){IIIll(
"\x75\x73\x62\x64\x5f\x6d\x63\x5f\x77\x72\x69\x74\x65\x3a\x20\x52\x45\x4d\x45\x58\x43\x4c\x55\x44\x45\x20\x63\x6f\x6d\x6d\x61\x6e\x64\x20\x72\x65\x63\x65\x69\x76\x65\x64" "\n"
);lIlll=lIllIlII(IIlII,lllIIl+(0x16f5+909-0x1a78),IlIII-(0x1b29+2145-0x2380));}
else if(strnicmp(lllIIl,"\x73\x65\x74\x6d\x6f\x64\x65",(0x109+7500-0x1e4e))==
(0x1229+1112-0x1681)){IIIll(
"\x75\x73\x62\x64\x5f\x6d\x63\x5f\x77\x72\x69\x74\x65\x3a\x20\x53\x45\x54\x4d\x4f\x44\x45\x20\x63\x6f\x6d\x6d\x61\x6e\x64\x20\x72\x65\x63\x65\x69\x76\x65\x64" "\n"
);lIlll=lIlIIllII(IIlII,lllIIl+(0x431+1192-0x8d2),IlIII-(0xcf7+93-0xd4d));}else 
if(strnicmp(lllIIl,"\x71\x75\x69\x72\x6b\x73",(0x1b12+2336-0x242c))==
(0x125f+990-0x163d)){IIIll(
"\x75\x73\x62\x64\x5f\x6d\x63\x5f\x77\x72\x69\x74\x65\x3a\x20\x51\x55\x49\x52\x4b\x53\x20\x63\x6f\x6d\x6d\x61\x6e\x64\x20\x72\x65\x63\x65\x69\x76\x65\x64" "\n"
);lIlll=lIllllIIl(IIlII,lllIIl+(0x752+3575-0x1543),IlIII-(0x61b+0-0x615));}
#endif 
#ifdef _USBD_ENABLE_VHCI_
if(strnicmp(lllIIl,"\x70\x6c\x75\x67",(0x1126+556-0x134e))==(0x1f8+1458-0x7aa)){
IIIll(
"\x75\x73\x62\x64\x5f\x6d\x63\x5f\x77\x72\x69\x74\x65\x3a\x20\x50\x4c\x55\x47\x20\x63\x6f\x6d\x6d\x61\x6e\x64\x20\x72\x65\x63\x65\x69\x76\x65\x64" "\n"
);lIlll=lllIIlII(IIlII,lllIIl+(0x21f+992-0x5fb),IlIII-(0x19f5+637-0x1c6e));}else
 if(strnicmp(lllIIl,"\x75\x6e\x70\x6c\x75\x67",(0x474+639-0x6ed))==
(0xcff+1184-0x119f)){IIIll(
"\x75\x73\x62\x64\x5f\x6d\x63\x5f\x77\x72\x69\x74\x65\x3a\x20\x55\x4e\x50\x4c\x55\x47\x20\x63\x6f\x6d\x6d\x61\x6e\x64\x20\x72\x65\x63\x65\x69\x76\x65\x64" "\n"
);lIlll=lIIllIIlI(IIlII,lllIIl+(0x1af4+2345-0x2417),IlIII-(0x1723+905-0x1aa6));}
else if(strnicmp(lllIIl,"\x75\x73\x62\x33\x73\x75\x70\x70\x6f\x72\x74",
(0x3fc+8882-0x26a3))==(0x551+558-0x77f)){IIIll(
"\x75\x73\x62\x64\x5f\x6d\x63\x5f\x77\x72\x69\x74\x65\x3a\x20\x55\x53\x42\x33\x53\x55\x50\x50\x4f\x52\x54\x20\x63\x6f\x6d\x6d\x61\x6e\x64\x20\x72\x65\x63\x65\x69\x76\x65\x64" "\n"
);
#if KERNEL_GT_EQ((0xcb2+3543-0x1a87),(0x1233+3926-0x2183),(0x1433+1594-0x1a46)) \
|| RHEL_RELEASE_GT_EQ((0x7e7+2512-0x11b1),(0x1678+3190-0x22eb)) 
lIlll=(0x172+2629-0xbb7);
#else
lIlll=-EINVAL;
#endif
}
#endif 
}while((0x172+5365-0x1667));if(lIlll==(0x2246+360-0x23ae))lIlll=IlIII;IIIll(
"\x75\x73\x62\x64\x5f\x6d\x63\x5f\x77\x72\x69\x74\x65\x3a\x20\x2d\x2d\x20\x72\x65\x73\x75\x6c\x74\x3d\x25\x6c\x75" "\n"
,(unsigned long)lIlll);return lIlll;}long IIlIlllIl(void*context,unsigned int 
IlIllI,unsigned long IllIll){IIIll(
"\x75\x73\x62\x64\x5f\x6d\x63\x5f\x69\x6f\x63\x74\x6c" "\n");return
(0x228c+951-0x2643);}
#ifdef CONFIG_COMPAT
long lIIIlllI(void*context,unsigned int IlIllI,unsigned long IllIll){IIIll(
"\x75\x73\x62\x64\x5f\x6d\x63\x5f\x63\x6f\x6d\x70\x61\x74\x5f\x69\x6f\x63\x74\x6c" "\n"
);return(0x2a0+3658-0x10ea);}
#endif
int IIlIlIlll(void*context){struct llIll*lllll=context;IIIll(
"\x75\x73\x62\x64\x5f\x6d\x63\x5f\x6f\x70\x65\x6e" "\n");IllIllII(lllll->llIllI)
;return(0x15cf+1103-0x1a1e);}int lllIIIll(void*context){struct llIll*lllll=
context;IIIll(
"\x75\x73\x62\x64\x5f\x6d\x63\x5f\x72\x65\x6c\x65\x61\x73\x65" "\n");IllIllII(
lllll->llIllI);return(0xacf+1553-0x10e0);}unsigned int IIIllIlI(void*context,
struct file*IllIIl,poll_table*lllIII){struct llIll*lllll=context;poll_wait(
IllIIl,&lllll->llIllI->IIIllIll,lllIII);if(lllll->llIllI->lllllIll){IIIll(
"\x75\x73\x62\x64\x5f\x6d\x63\x5f\x70\x6f\x6c\x6c\x3a\x20\x6e\x75\x6d\x5f\x65\x6e\x74\x72\x69\x65\x73\x3d\x25\x64" "\n"
,lllll->llIllI->lllllIll);return((POLLOUT|POLLWRNORM)|(POLLIN|POLLRDNORM));}
return(POLLOUT|POLLWRNORM);}
#ifdef _USBD_ENABLE_STUB_
int lIIIIlll(struct llIll*IIlII,const char*IlIIl,size_t IlIII){int lIlll=-EFAULT
;struct IllII*IlIlI=NULL;IIIll(
"\x75\x73\x62\x64\x5f\x6d\x63\x5f\x73\x68\x61\x72\x65\x3a\x20\x2b\x2b" "\n");do{
u32 vid,IIlIIl,IIIlII;char bus_id[IllIlII]={(0x16e0+3020-0x22ac)};char llIIIII[
(0x14a3+2831-0x1f80)];int lllIlIIII=(0x1114+21-0x1129);if(sscanf(IlIIl,
"\x25\x78\x2d\x25\x78\x20\x25\x73\x20\x25\x78",&vid,&IIlIIl,bus_id,&IIIlII)!=
(0x8c6+3864-0x17da)){IIIll(
"\x75\x73\x62\x64\x5f\x6d\x63\x5f\x73\x68\x61\x72\x65\x3a\x20\x73\x73\x63\x61\x6e\x66\x20\x66\x61\x69\x6c\x65\x64" "\n"
);lIlll=-EINVAL;break;}IIIll(
"\x75\x73\x62\x64\x5f\x6d\x63\x5f\x73\x68\x61\x72\x65\x3a\x20\x64\x65\x76\x69\x63\x65\x20\x69\x73\x20\x76\x69\x64\x3d\x25\x78\x20\x70\x69\x64\x3d\x25\x78\x20\x62\x75\x73\x5f\x69\x64\x3d\x25\x73\x20\x68\x61\x6e\x64\x6c\x65\x3d\x25\x75" "\n"
,vid,IIlIIl,bus_id,IIIlII);IlIlI=IlllIIlI(vid,IIlIIl,bus_id);if(IlIlI){IIIll(
"\x75\x73\x62\x64\x5f\x6d\x63\x5f\x73\x68\x61\x72\x65\x3a\x20\x64\x65\x76\x69\x63\x65\x20\x61\x6c\x72\x65\x61\x64\x79\x20\x73\x68\x61\x72\x65\x64\x2c\x20\x72\x65\x66\x72\x65\x73\x68\x69\x6e\x67\x20\x69\x74\x27\x73\x20\x73\x74\x61\x74\x65" "\n"
);lllIlIIII=(0x113b+3438-0x1ea8);}else{IlIlI=llllIIlI(vid,IIlIIl,bus_id);if(
IlIlI==NULL){IIIll(
"\x75\x73\x62\x64\x5f\x6d\x63\x5f\x73\x68\x61\x72\x65\x3a\x20\x75\x73\x62\x64\x5f\x73\x74\x75\x62\x5f\x63\x72\x65\x61\x74\x65\x20\x66\x61\x69\x6c\x65\x64" "\n"
);lIlll=-ENOMEM;break;}}IlIlI->IIIlII=IIIlII;snprintf(llIIIII,sizeof(llIIIII)/
sizeof(llIIIII[(0x6ed+1578-0xd17)]),
"\x64\x65\x76\x6e\x75\x6d\x20\x25\x2e\x38\x78\x20\x25\x64\x20\x25\x64",IlIlI->
IIIlII,IIIlIlIl,IlIlI->IIlII->IlllIl);lIlll=lllIlIlI(IIlII,llIIIII);if(lIlll<
(0x205c+1306-0x2576)){IIIll(
"\x75\x73\x62\x64\x5f\x6d\x63\x5f\x73\x68\x61\x72\x65\x3a\x20\x75\x73\x62\x64\x5f\x6d\x63\x5f\x61\x64\x64\x5f\x65\x76\x65\x6e\x74\x20\x66\x61\x69\x6c\x65\x64\x20\x77\x69\x74\x68\x20\x65\x72\x72\x6f\x72\x20\x25\x64" "\n"
,lIlll);lIlll=-ENOMEM;break;}if(lllIlIIII)IllIIlll(IlIlI);llIllII(IlIlI);lIlll=
(0x509+5269-0x199e);}while((0x283+4962-0x15e5));if(lIlll!=(0x1794+3898-0x26ce)){
if(IlIlI)IlIlllII(IlIlI);
}IIIll(
"\x75\x73\x62\x64\x5f\x6d\x63\x5f\x73\x68\x61\x72\x65\x3a\x20\x2d\x2d\x20\x72\x65\x73\x75\x6c\x74\x3d\x25\x64" "\n"
,lIlll);return lIlll;}int llIlllll(struct llIll*IIlII,const char*IlIIl,size_t 
IlIII){u32 IIIlII;struct IllII*IlIlI;int lIlll=-EFAULT;IIIll(
"\x75\x73\x62\x64\x5f\x6d\x63\x5f\x75\x6e\x73\x68\x61\x72\x65\x3a\x20\x2b\x2b" "\n"
);do{if(sscanf(IlIIl,"\x25\x78",&IIIlII)!=(0x1e90+390-0x2015)){IIIll(
"\x75\x73\x62\x64\x5f\x6d\x63\x5f\x75\x6e\x73\x68\x61\x72\x65\x3a\x20\x73\x73\x63\x61\x6e\x66\x20\x66\x61\x69\x6c\x65\x64" "\n"
);lIlll=-EINVAL;break;}IIIll(
"\x75\x73\x62\x64\x5f\x6d\x63\x5f\x75\x6e\x73\x68\x61\x72\x65\x3a\x20\x68\x61\x6e\x64\x6c\x65\x3d\x25\x75" "\n"
,IIIlII);IlIlI=IIllIIIl(IIIlII);if(IlIlI==NULL){IIIll(
"\x75\x73\x62\x64\x5f\x6d\x63\x5f\x75\x6e\x73\x68\x61\x72\x65\x3a\x20\x64\x65\x76\x69\x63\x65\x20\x77\x69\x74\x68\x20\x68\x61\x6e\x64\x6c\x65\x20\x25\x75\x20\x69\x73\x20\x6e\x6f\x74\x20\x66\x6f\x75\x6e\x64" "\n"
,IIIlII);lIlll=-ENODEV;break;}IllIIlIl(IlIlI,IIIlIIlI);IlIlllII(IlIlI);
llIllII(IlIlI);lIlll=(0x805+5492-0x1d79);}while((0xc61+1343-0x11a0));IIIll(
"\x75\x73\x62\x64\x5f\x6d\x63\x5f\x75\x6e\x73\x68\x61\x72\x65\x3a\x20\x2d\x2d\x20\x72\x65\x73\x75\x6c\x74\x3d\x25\x64" "\n"
,lIlll);return lIlll;}int IIIlIIllI(struct llIll*IIlII,const char*IlIIl,size_t 
IlIII){u32 IIIlII;int IIIIllll;struct IllII*IlIlI;int lIlll=-EFAULT;IIIll(
"\x75\x73\x62\x64\x5f\x6d\x63\x5f\x72\x65\x73\x65\x74\x3a\x20\x2b\x2b" "\n");do{
struct usb_device*lIIII;if(sscanf(IlIIl,"\x25\x78\x20\x25\x64",&IIIlII,&IIIIllll
)!=(0x86d+3989-0x1800)){IIIll(
"\x75\x73\x62\x64\x5f\x6d\x63\x5f\x72\x65\x73\x65\x74\x3a\x20\x73\x73\x63\x61\x6e\x66\x20\x66\x61\x69\x6c\x65\x64" "\n"
);lIlll=-EINVAL;break;}IIIll(
"\x75\x73\x62\x64\x5f\x6d\x63\x5f\x72\x65\x73\x65\x74\x3a\x20\x68\x61\x6e\x64\x6c\x65\x3d\x25\x75\x20\x6d\x65\x74\x68\x6f\x64\x3d\x25\x64" "\n"
,IIIlII,IIIIllll);IlIlI=IIllIIIl(IIIlII);if(IlIlI==NULL){IIIll(
"\x75\x73\x62\x64\x5f\x6d\x63\x5f\x72\x65\x73\x65\x74\x3a\x20\x64\x65\x76\x69\x63\x65\x20\x77\x69\x74\x68\x20\x68\x61\x6e\x64\x6c\x65\x20\x25\x75\x20\x69\x73\x20\x6e\x6f\x74\x20\x66\x6f\x75\x6e\x64" "\n"
,IIIlII);lIlll=-ENODEV;break;}lIIII=lIllIIlI(IlIlI);if(lIIII){IlllIlll(IlIlI,
lIIII,IIIIllll);IIlllllI(IlIlI,lIIII);}llIllII(IlIlI);lIlll=(0x229a+30-0x22b8);}
while((0x90f+557-0xb3c));IIIll(
"\x75\x73\x62\x64\x5f\x6d\x63\x5f\x72\x65\x73\x65\x74\x3a\x20\x2d\x2d\x20\x72\x65\x73\x75\x6c\x74\x3d\x25\x64" "\n"
,lIlll);return lIlll;}int IIIIlllll(struct llIll*IIlII,const char*IlIIl,size_t 
IlIII){int lIlll=-EFAULT;IIIll(
"\x75\x73\x62\x64\x5f\x6d\x63\x5f\x61\x64\x64\x65\x78\x63\x6c\x75\x64\x65\x3a\x20\x2b\x2b" "\n"
);do{u32 vid,IIlIIl,IIIlII;char bus_id[IllIlII]={(0xf1+246-0x1e7)};struct 
IlIIIlll*IIllll;unsigned long flags;if(sscanf(IlIIl,
"\x25\x78\x2d\x25\x78\x20\x25\x73\x20\x25\x78",&vid,&IIlIIl,bus_id,&IIIlII)!=
(0x2275+568-0x24a9)){IIIll(
"\x75\x73\x62\x64\x5f\x6d\x63\x5f\x61\x64\x64\x65\x78\x63\x6c\x75\x64\x65\x3a\x20\x73\x73\x63\x61\x6e\x66\x20\x66\x61\x69\x6c\x65\x64" "\n"
);lIlll=-EINVAL;break;}IIIll(
"\x75\x73\x62\x64\x5f\x6d\x63\x5f\x61\x64\x64\x65\x78\x63\x6c\x75\x64\x65\x3a\x20\x64\x65\x76\x69\x63\x65\x20\x69\x73\x20\x76\x69\x64\x3d\x25\x78\x20\x70\x69\x64\x3d\x25\x78\x20\x62\x75\x73\x5f\x69\x64\x3d\x25\x73\x20\x68\x61\x6e\x64\x6c\x65\x3d\x25\x75" "\n"
,vid,IIlIIl,bus_id,IIIlII);IIllll=kmalloc(sizeof(struct IlIIIlll),GFP_KERNEL);if
(IIllll==NULL){IIIll(
"\x75\x73\x62\x64\x5f\x6d\x63\x5f\x61\x64\x64\x65\x78\x63\x6c\x75\x64\x65\x3a\x20\x6e\x6f\x20\x6d\x65\x6d\x6f\x72\x79" "\n"
);lIlll=-ENOMEM;break;}INIT_LIST_HEAD(&IIllll->lIIIl);IIllll->IIIlII=IIIlII;
IIllll->vid=vid;IIllll->IIlIIl=IIlIIl;strncpy(IIllll->bus_id,bus_id,IllIlII);
spin_lock_irqsave(&lIlIlIl,flags);list_add_tail(&IIllll->lIIIl,&IIllIIl);
spin_unlock_irqrestore(&lIlIlIl,flags);lIlll=(0x7f3+1113-0xc4c);}while(
(0xe75+2887-0x19bc));IIIll(
"\x75\x73\x62\x64\x5f\x6d\x63\x5f\x61\x64\x64\x65\x78\x63\x6c\x75\x64\x65\x3a\x20\x2d\x2d\x20\x72\x65\x73\x75\x6c\x74\x3d\x25\x64" "\n"
,lIlll);return lIlll;}int lIllIlII(struct llIll*IIlII,const char*IlIIl,size_t 
IlIII){u32 IIIlII;int lIlll=-EFAULT;IIIll(
"\x75\x73\x62\x64\x5f\x6d\x63\x5f\x72\x65\x6d\x65\x78\x63\x6c\x75\x64\x65\x3a\x20\x2b\x2b" "\n"
);do{unsigned long flags;struct IlIIIlll*IIllll;if(sscanf(IlIIl,"\x25\x78",&
IIIlII)!=(0x6db+7585-0x247b)){IIIll(
"\x75\x73\x62\x64\x5f\x6d\x63\x5f\x72\x65\x6d\x65\x78\x63\x6c\x75\x64\x65\x3a\x20\x73\x73\x63\x61\x6e\x66\x20\x66\x61\x69\x6c\x65\x64" "\n"
);lIlll=-EINVAL;break;}IIIll(
"\x75\x73\x62\x64\x5f\x6d\x63\x5f\x72\x65\x6d\x65\x78\x63\x6c\x75\x64\x65\x3a\x20\x68\x61\x6e\x64\x6c\x65\x3d\x25\x75" "\n"
,IIIlII);spin_lock_irqsave(&lIlIlIl,flags);list_for_each_entry(IIllll,&IIllIIl,
lIIIl){if(IIllll->IIIlII==IIIlII){list_del(&IIllll->lIIIl);kfree(IIllll);IIIll(
"\x75\x73\x62\x64\x5f\x6d\x63\x5f\x72\x65\x6d\x65\x78\x63\x6c\x75\x64\x65\x3a\x20\x65\x78\x63\x6c\x75\x73\x69\x6f\x6e\x20\x72\x65\x6d\x6f\x76\x65\x64" "\n"
);break;}}spin_unlock_irqrestore(&lIlIlIl,flags);lIlll=(0xfca+2553-0x19c3);}
while((0x518+2690-0xf9a));IIIll(
"\x75\x73\x62\x64\x5f\x6d\x63\x5f\x72\x65\x6d\x65\x78\x63\x6c\x75\x64\x65\x3a\x20\x2d\x2d\x20\x72\x65\x73\x75\x6c\x74\x3d\x25\x64" "\n"
,lIlll);return lIlll;}int lIlIIllII(struct llIll*IIlII,const char*IlIIl,size_t 
IlIII){int lIlll=-EFAULT;IIIll(
"\x75\x73\x62\x64\x5f\x6d\x63\x5f\x73\x65\x74\x6d\x6f\x64\x65\x3a\x20\x2b\x2b" "\n"
);do{u32 lIIlllll;if(sscanf(IlIIl,"\x25\x78",&lIIlllll)!=(0x38f+6755-0x1df1)){
IIIll(
"\x75\x73\x62\x64\x5f\x6d\x63\x5f\x73\x65\x74\x6d\x6f\x64\x65\x3a\x20\x73\x73\x63\x61\x6e\x66\x20\x66\x61\x69\x6c\x65\x64" "\n"
);lIlll=-EINVAL;break;}IIIll(
"\x75\x73\x62\x64\x5f\x6d\x63\x5f\x73\x65\x74\x6d\x6f\x64\x65\x3a\x20\x6d\x6f\x64\x65\x3d\x25\x75" "\n"
,lIIlllll);lIIIIIII=lIIlllll;lIlll=(0x134b+2008-0x1b23);}while(
(0x1247+2801-0x1d38));IIIll(
"\x75\x73\x62\x64\x5f\x6d\x63\x5f\x73\x65\x74\x6d\x6f\x64\x65\x3a\x20\x2d\x2d\x20\x72\x65\x73\x75\x6c\x74\x3d\x25\x64" "\n"
,lIlll);return lIlll;}int lIllllIIl(struct llIll*IIlII,const char*IlIIl,size_t 
IlIII){u32 IIIlII;int lIllIlI;struct IllII*IlIlI;int lIlll=-EFAULT;IIIll(
"\x75\x73\x62\x64\x5f\x6d\x63\x5f\x71\x75\x69\x72\x6b\x73\x3a\x20\x2b\x2b" "\n")
;do{if(sscanf(IlIIl,"\x25\x78\x20\x25\x64",&IIIlII,&lIllIlI)!=
(0x1883+1893-0x1fe6)){IIIll(
"\x75\x73\x62\x64\x5f\x6d\x63\x5f\x71\x75\x69\x72\x6b\x73\x3a\x20\x73\x73\x63\x61\x6e\x66\x20\x66\x61\x69\x6c\x65\x64" "\n"
);lIlll=-EINVAL;break;}IIIll(
"\x75\x73\x62\x64\x5f\x6d\x63\x5f\x71\x75\x69\x72\x6b\x73\x3a\x20\x68\x61\x6e\x64\x6c\x65\x3d\x25\x75\x20\x71\x75\x69\x72\x6b\x73\x3d\x25\x64" "\n"
,IIIlII,lIllIlI);IlIlI=IIllIIIl(IIIlII);if(IlIlI==NULL){IIIll(
"\x75\x73\x62\x64\x5f\x6d\x63\x5f\x71\x75\x69\x72\x6b\x73\x3a\x20\x64\x65\x76\x69\x63\x65\x20\x77\x69\x74\x68\x20\x68\x61\x6e\x64\x6c\x65\x20\x25\x75\x20\x69\x73\x20\x6e\x6f\x74\x20\x66\x6f\x75\x6e\x64" "\n"
,IIIlII);lIlll=-ENODEV;break;}IlIlI->lIllIlI=lIllIlI;llIllII(IlIlI);lIlll=
(0x11cc+4166-0x2212);}while((0x3a2+5112-0x179a));IIIll(
"\x75\x73\x62\x64\x5f\x6d\x63\x5f\x71\x75\x69\x72\x6b\x73\x3a\x20\x2d\x2d\x20\x72\x65\x73\x75\x6c\x74\x3d\x25\x64" "\n"
,lIlll);return lIlll;}
#endif 
#ifdef _USBD_ENABLE_VHCI_
int lllIIlII(struct llIll*IIlII,const char*IlIIl,size_t IlIII){int lIlll=-EFAULT
;struct IIIII*lllll=NULL;IIIll(
"\x75\x73\x62\x64\x5f\x6d\x63\x5f\x70\x6c\x75\x67\x3a\x20\x2b\x2b" "\n");do{u32 
IlIlIll,IllllIl;char llIIIII[(0x157f+272-0x1653)];char IIIlIlll[
(0xfe5+2340-0x18ff)];int speed;if(sscanf(IlIIl,
"\x25\x78\x20\x25\x78\x20\x25\x35\x73",&IlIlIll,&IllllIl,IIIlIlll)!=
(0x72f+2466-0x10ce)){IIIll(
"\x75\x73\x62\x64\x5f\x6d\x63\x5f\x70\x6c\x75\x67\x3a\x20\x73\x73\x63\x61\x6e\x66\x20\x66\x61\x69\x6c\x65\x64" "\n"
);lIlll=-EINVAL;break;}if(strnicmp(IIIlIlll,"\x6c\x6f\x77",(0x162d+485-0x180f))
==(0x16e8+3863-0x25ff)){speed=USB_SPEED_LOW;}else if(strnicmp(IIIlIlll,
"\x66\x75\x6c\x6c",(0x17e1+96-0x183d))==(0x1aa0+254-0x1b9e)){speed=
USB_SPEED_FULL;}else if(strnicmp(IIIlIlll,"\x68\x69\x67\x68",(0x2fb+420-0x49b))
==(0xaf1+2617-0x152a)){speed=USB_SPEED_HIGH;}else if(strnicmp(IIIlIlll,
"\x73\x75\x70\x65\x72",(0x6c7+3727-0x1551))==(0x16c5+585-0x190e)){
#if KERNEL_GT_EQ((0xc25+2367-0x1562),(0x162+8640-0x231c),(0x1af9+1355-0x201d)) \
|| RHEL_RELEASE_GT_EQ((0xa42+2151-0x12a3),(0x8d+1987-0x84d)) 
speed=USB_SPEED_SUPER;
#else
IIIIlll(
"\x55\x53\x42\x20\x33\x2e\x30\x20\x69\x73\x20\x6e\x6f\x74\x20\x73\x75\x70\x70\x6f\x72\x74\x65\x64\x20\x6f\x6e\x20\x74\x68\x69\x73\x20\x6b\x65\x72\x6e\x65\x6c\x2c\x20\x75\x73\x65\x20\x6b\x65\x72\x6e\x65\x6c\x20\x32\x2e\x36\x2e\x33\x39\x20\x6f\x72\x20\x6e\x65\x77\x65\x72" "\n"
);lIlll=-EINVAL;break;
#endif
}else{IIIll(
"\x75\x73\x62\x64\x5f\x6d\x63\x5f\x70\x6c\x75\x67\x3a\x20\x69\x6e\x76\x61\x6c\x69\x64\x20\x64\x65\x76\x69\x63\x65\x20\x73\x70\x65\x65\x64" "\n"
);lIlll=-EINVAL;break;}lllll=lIIlIlIl(IlIlIll,IllllIl);if(lllll!=NULL){IIIIllI(
lllll);lllll=NULL;IIIll(
"\x75\x73\x62\x64\x5f\x6d\x63\x5f\x70\x6c\x75\x67\x3a\x20\x64\x65\x76\x69\x63\x65\x20\x77\x69\x74\x68\x20\x68\x61\x6e\x64\x6c\x65\x20\x25\x75\x20\x25\x75\x20\x69\x73\x20\x61\x6c\x72\x65\x61\x64\x79\x20\x70\x6c\x75\x67\x67\x65\x64" "\n"
,IlIlIll,IllllIl);lIlll=-EISCONN;break;}lllll=IlIIIIlIl(IlIlIll,IllllIl,speed);
if(lllll==NULL){IIIll(
"\x75\x73\x62\x64\x5f\x6d\x63\x5f\x70\x6c\x75\x67\x3a\x20\x75\x73\x62\x64\x5f\x76\x68\x63\x69\x5f\x64\x65\x76\x69\x63\x65\x5f\x63\x72\x65\x61\x74\x65\x20\x66\x61\x69\x6c\x65\x64" "\n"
);lIlll=-ENOMEM;break;}snprintf(llIIIII,sizeof(llIIIII)/sizeof(llIIIII[
(0xa61+1697-0x1102)]),
"\x76\x64\x65\x76\x6e\x75\x6d\x20\x25\x2e\x38\x78\x20\x25\x2e\x38\x78\x20\x25\x64\x20\x25\x64"
,lllll->IlIlIll,lllll->IllllIl,IIIlIlIl,lllll->IIlII->IlllIl);lIlll=lllIlIlI(
IIlII,llIIIII);if(lIlll<(0x757+7206-0x237d)){IIIll(
"\x75\x73\x62\x64\x5f\x6d\x63\x5f\x73\x68\x61\x72\x65\x3a\x20\x75\x73\x62\x64\x5f\x6d\x63\x5f\x61\x64\x64\x5f\x65\x76\x65\x6e\x74\x20\x66\x61\x69\x6c\x65\x64\x20\x77\x69\x74\x68\x20\x65\x72\x72\x6f\x72\x20\x25\x64" "\n"
,lIlll);lIlll=-ENOMEM;break;}llIlIlIll(lllll);lIlll=(0x3cf+3016-0xf97);}while(
(0x299+2206-0xb37));if(lIlll!=(0x1b45+852-0x1e99)){if(lllll)IllllIIl(lllll);}
IIIll(
"\x75\x73\x62\x64\x5f\x6d\x63\x5f\x70\x6c\x75\x67\x3a\x20\x2d\x2d\x20\x72\x65\x73\x75\x6c\x74\x3d\x25\x64" "\n"
,lIlll);return lIlll;}int lIIllIIlI(struct llIll*IIlII,const char*IlIIl,size_t 
IlIII){int lIlll=-EFAULT;struct IIIII*lllll;IIIll(
"\x75\x73\x62\x64\x5f\x6d\x63\x5f\x75\x6e\x70\x6c\x75\x67\x3a\x20\x2b\x2b" "\n")
;do{u32 IlIlIll,IllllIl;if(sscanf(IlIIl,"\x25\x78\x20\x25\x78",&IlIlIll,&IllllIl
)!=(0x4d8+4060-0x14b2)){IIIll(
"\x75\x73\x62\x64\x5f\x6d\x63\x5f\x75\x6e\x70\x6c\x75\x67\x3a\x20\x73\x73\x63\x61\x6e\x66\x20\x66\x61\x69\x6c\x65\x64" "\n"
);lIlll=-EINVAL;break;}lllll=lIIlIlIl(IlIlIll,IllllIl);if(lllll==NULL){IIIll(
"\x75\x73\x62\x64\x5f\x6d\x63\x5f\x75\x6e\x70\x6c\x75\x67\x3a\x20\x64\x65\x76\x69\x63\x65\x20\x6f\x6e\x20\x77\x69\x74\x68\x20\x68\x61\x6e\x64\x6c\x65\x20\x25\x75\x20\x25\x75\x20\x69\x73\x20\x6e\x6f\x74\x20\x66\x6f\x75\x6e\x64" "\n"
,IlIlIll,IllllIl);lIlll=-ENODEV;break;}llIIIIll(lllll);IllllIIl(lllll);IIIIllI(
lllll);
lIlll=(0x1123+2593-0x1b44);}while((0xd73+177-0xe24));IIIll(
"\x75\x73\x62\x64\x5f\x6d\x63\x5f\x75\x6e\x70\x6c\x75\x67\x3a\x20\x2d\x2d\x20\x72\x65\x73\x75\x6c\x74\x3d\x25\x64" "\n"
,lIlll);return lIlll;}
#endif 

