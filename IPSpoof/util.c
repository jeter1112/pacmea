#include<linux/kernel.h>
#include <linux/inetdevice.h>

#define GET_PORT(netnum) ntohs(netnum)
#define SET_PORT(hnum) htons(hnum)
u32 IP_TO_NUM(char* str)
{
    u8 num[4];
    int a,b,c,d;
    sscanf(str, "%d.%d.%d.%d", &a,&b,&c,&d);
    num[0]=a; num[1]=b; num[2]=c; num[3]=d;
    return *(u32 *)num;
}

static void NUM_TO_IP(u32 num,char*str)
{
    snprintf(str, 16, "%pI4", &num);
}

void tcp_dump(const char* key, struct sk_buff *skb)
{
    char saddr[16], daddr[16];
    struct iphdr* iph= ip_hdr(skb);
    struct tcphdr *tcph = tcp_hdr(skb);
    NUM_TO_IP(iph->saddr, saddr);
    NUM_TO_IP(iph->daddr, daddr);
    printk("[%s]\
            \n\tSeq: 0x%08x; ACK: 0x%08x\
            \n\tSrc: %s, Dst:%s, %d -> %d\
            \n\tSYN %d; ACK %d; FIN %d; RST %d; PSH %d\n", \
            key,
            ntohs(tcph->seq), ntohs(tcph->ack_seq), \
            saddr, daddr, ntohs(tcph->source), ntohs(tcph->dest), \
            tcph->syn, tcph->ack, tcph->fin, tcph->rst, tcph->psh);
}

u32 getWlsAddr(const char *if_name)
{
    u32 ipv4 = 0;
    struct net_device* dev;
    struct in_device* pdev;

    for_each_netdev(&init_net, dev)
    {
       
        printk("%s\n",dev->name);
        if(strcmp(dev->name,"wlp3s0")==0)
        {
            pdev = (struct in_device *)dev->ip_ptr;
            ipv4 = pdev->ifa_list->ifa_address;
            char x[16];
            NUM_TO_IP(ipv4,x);
            printk("%s\n",x);   
        }
    }
    

    return ipv4;
}