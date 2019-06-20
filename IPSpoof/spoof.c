#include<linux/module.h>
#include<linux/netfilter.h>
#include<linux/ip.h>
#include<linux/tcp.h>
#include<linux/inet.h>
#include<net/tcp.h>
#include<linux/udp.h>
#include<linux/netfilter_ipv4.h>
#include<linux/kernel.h>
#include <linux/skbuff.h>
#include "util.c"

#define EncryIP  "192.168.1.221"

#define EncryPort 5210

static u32 realaddr=0;
static struct net_device* wls;



unsigned int ip_tx(void *priv,
			       struct sk_buff *skb,
			       const struct nf_hook_state *state)
{
    struct iphdr* iph;
    iph=(struct iphdr*)skb_network_header(skb);
    struct tcphdr *tcph;
    if ( (iph->protocol == IPPROTO_TCP)) {
        
   
        
       
    tcph=tcp_hdr(skb);
    u16 port=ntohs(tcph->dest);
    
    if(port==EncryPort)
    {
        
     

        iph->saddr = IP_TO_NUM("192.168.1.221");


        skb->ip_summed = CHECKSUM_NONE; //stop offloading
        skb->csum_valid = 0;
        iph->check = 0;
        iph->check = ip_fast_csum((u8 *)iph, iph->ihl);

        if(skb_is_nonlinear(skb))
            skb_linearize(skb);

      
        unsigned int tcplen;

        tcph = tcp_hdr(skb);
        skb->csum =0;
        tcplen = ntohs(iph->tot_len) - iph->ihl*4;
        tcph->check = 0;
        tcph->check = tcp_v4_check(tcplen, iph->saddr, iph->daddr, csum_partial((char *)tcph, tcplen, 0));


        tcp_dump("OUTBOUND",skb);
        
    }
    
        
    }

    return NF_ACCEPT;
}

unsigned int ip_rx(void *priv,
			       struct sk_buff *skb,
			       const struct nf_hook_state *state)
{
    struct iphdr* iph;
    
    iph=(struct iphdr*)skb_network_header(skb);
    struct tcphdr *tcph;
    if ( (iph->protocol == IPPROTO_TCP)) {
        
        tcph=tcp_hdr(skb);

        u16 port=ntohs(tcph->source);
        
        if(port==EncryPort)
        {   
            

            iph->daddr = realaddr;

            //skb->dev=wls;
            skb->ip_summed = CHECKSUM_NONE; //stop offloading
            skb->csum_valid = 0;
            iph->check = 0;
            iph->check = ip_fast_csum((u8 *)iph, iph->ihl);

            if(skb_is_nonlinear(skb))
                skb_linearize(skb);

        
            unsigned int tcplen;

            tcph = tcp_hdr(skb);
            skb->csum =0;
            tcplen = ntohs(iph->tot_len) - iph->ihl*4;
            tcph->check = 0;
            tcph->check = tcp_v4_check(tcplen, iph->saddr, iph->daddr, csum_partial((char *)tcph, tcplen, 0));
            tcp_dump("INBOUND",skb);
        }

        u16 nport=ntohs(tcph->dest);

       
        
    }

    return NF_ACCEPT;
}

static struct nf_hook_ops ip_in={
    .hook=ip_rx,
    .hooknum=NF_INET_PRE_ROUTING,
    .pf=PF_INET,
    .priority=NF_IP_PRI_FIRST,
};
static struct nf_hook_ops ip_out=
{
    .hook=ip_tx,
    .hooknum=4,
    .pf=PF_INET,
    .priority=NF_IP_PRI_LAST,
};

static int __init __init_nf(void)
{
    printk(KERN_INFO"Kfollow module init.\n");
    realaddr=getWlsAddr("wls");
    wls=dev_get_by_name(&init_net,"wlp3s0");
    nf_register_net_hook(&init_net,&ip_in);
    nf_register_net_hook(&init_net,&ip_out);
    return 0;
}

static void  __exit __exit_nf(void)
{
    printk(KERN_INFO"Kfollow module exit.\n");
    nf_unregister_net_hook(&init_net,&ip_in);
    nf_unregister_net_hook(&init_net,&ip_out);

}

module_init(__init_nf);
module_exit(__exit_nf);

MODULE_AUTHOR("Jeter");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Netfilter TCP/UDP infor filter.");