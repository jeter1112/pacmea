""" Problem classification:
        when I measure throughput by using iperfs with several hosts.
        I need to redirect output  to the txt files;
        So The problem arises: How to get the data from files and deliver them to the right test case to analyse?
    get the file names should be splited ----> map files to the output test cases ---> file to data and to test cases.
"""





import sys,os


di="/home/jeter/Downloads/311/"
# ops=[]
# def file_name(file_dir): 
#     result=[]  
#     for root, dirs, files in os.walk(file_dir): 
#         for file in files:
#             if file.endswith(".txt"): 
#                 result.append(root+'/'+file)
#     return result
# ops+=file_name(di+'/test0')
# ops+=file_name(di+'/test1')
# ops+=file_name(di+'/test2')
# ops+=file_name(di+'/test3')
# print(ops)

# for f in ops:
#     result=[]
#     with open(f) as fi:
#         for cont in fi:
#             li=cont.split()
#             if len(li)== 8 and ( li[7][0] == 'M' or li[7][0]== 'K'):
#                 if li[7][0] == 'M':
#                     result.append(li[6])
#                 elif li[7][0]== 'K':
#                     num=str(float(li[6])/1000)
#                     result.append(num)
#     l=f.split('.')[0]+'.log'
#     print(l)
#     with open(l,'w') as li:
#         for cont in result:
#             li.writelines(cont+'\n')
            







def get_file_name_in_dir(file_dir,dir_pattern='test',file_pattern='0',out_dir='_data'):
    
    fs=[]
    ds=[]
    tokens={}
    
    dirs=os.listdir(file_dir)
    for di in dirs:
        if di.__contains__(dir_pattern):
            files=os.listdir(di)
            for fil in files:
                if fil.__contains__('txt'):
                    if fil.__contains__('0'):
                        # mkdir for data analysis
                        
                        dir_name=fil.split('0')[0]+out_dir
                        
                        n_dir=file_dir+dir_name
                        ds.append(n_dir)
                        tokens[fil.split('0')[0]]=n_dir
                        if not os.path.exists(n_dir):
                            os.mkdir(n_dir)
                        f_name=file_dir+di+'/'+fil
                        fs.append(f_name)
                    else:
                        f_name=file_dir+di+'/'+fil
                        fs.append(f_name)
            
    return [fs,dirs,tokens]   





def genrate_data_to_dir_from_file(file_name,dir_name):
    result=[]
    with open(file_name) as fi:
        for cont in fi:
            li=cont.split()
            if len(li)== 8 and ( li[7][0] == 'M' or li[7][0]== 'K'):
                if li[7][0] == 'M':
                    result.append(li[6])
                elif li[7][0]== 'K':
                    num=str(float(li[6])/1000)
                    result.append(num)
    log_file=dir_name+'/'+(file_name.split('/')[-1]).split('.')[0]+'.log'
    
    with open(log_file,'w') as lo:
        for cont in result:
            lo.writelines(cont+'\n')
    


def orig_to_data(fs,dirs,tokens):

    for file_name in fs:
        for token in tokens.keys():
            if file_name.split('/')[-1].__contains__(token):
                print(file_name+'\t'+token)
                dir_name=tokens[token]
                genrate_data_to_dir_from_file(file_name,dir_name)
                break

            

fs,dirs,tokens=get_file_name_in_dir(di)
orig_to_data(fs,dirs,tokens)


    
