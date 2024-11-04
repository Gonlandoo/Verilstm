#include <libsnark/common/default_types/r1cs_gg_ppzksnark_pp.hpp>
#include <libsnark/zk_proof_systems/ppzksnark/r1cs_gg_ppzksnark/r1cs_gg_ppzksnark.hpp>
#include <libsnark/gadgetlib1/pb_variable.hpp>
#include<iostream>
#include<stdio.h>
#include<vector>
#include <string>  
#include <vector>  
#include <fstream>  
#include <sstream>
#include <sys/time.h>  
#include <stdlib.h>
using namespace std;
using namespace libsnark;

static int hidden_size = 20;
static int input_size = 10;
static int ihl0_input[4*20][10];
static int ihl0_input_T[10][4*20];
static int ihl0_weight[4*20][10];
static int ihl0_bias[4*20];
static int ihl0_sys1[4*20][4*20];
static int ihl0_out[4*20][4*20];
static int ihl0_sys11[4*20][10*4*20];
static int ihl0_sys12[4*20][10*80];
static int weight_encoded_indexed[4*20*10];
static int encode_row[80];
static int encode_column[10];
static int index_encoded[4*20*10];



// // Define variables
// static pb_variable<FieldT> pb_weight[4*20][10];
// static pb_variable<FieldT> pb_input[4*20][10];
// static pb_variable<FieldT> pv_bias[4*20];
// static pb_variable<FieldT> pb_sys1[4*20][4*20];
// static pb_variable<FieldT> pb_out[4*20][4*20];
// static pb_variable<FieldT> pb_sys11[4*20][10*4*20];
// static pb_variable<FieldT> pb_sys12[4*20][9*80];
// static pb_variable<FieldT> pb_weight_encoded_indexed[4*20*10];
// static pb_variable<FieldT> pb_encode_row[80];
// static pb_variable<FieldT> pb_encode_column[10];

// typedef libff::Fr<default_r1cs_gg_ppzksnark_pp> FieldT;
// pb_variable<FieldT>ihl0Sym1_var[4*20][4*20];
// pb_variable<FieldT>ihl0Sym_var[4*20][4*20];
// pb_variable<FieldT>ihl0Sym2_var[4*20][4*20];

class compute_params
{
   public:
      void read_ihl0_input();
      void read_ihl0_weight();
      void read_ihl0_bias();
      void weight_encoded_query(); 
      void weightMulinput();
      void sysAddbias();
      void getsys11();
      void getsys12();
      void base_process();
      void encodedWeight_process();
};
void compute_params::read_ihl0_input()
{
    // ifstream inFile("/home/libsnarkdemo/libsnark_demo/src/data/conv1_input_im2col_nume__test_3.csv", ios::in);  
    ifstream inFile("/home/ashlyn/Documents/SNARK/libsnark_abc/src/data/l0_input_fixed_reshaped.csv", ios::in);
    string lineStr;  
    vector<vector<string>> strArray;  
    int i,j;
    i=0;
    char* end;
    // cout<<"conv1_input_nume"<<endl<<endl;
    if(inFile.fail())
        cout<<"读取文件失败"<<endl;

    else
    {
        string line;
        vector<string>words;
        string word;
        // 读取标题行
        // getline(inFile,line);
        istringstream sin;
        // 按行读取数据
        while(getline(inFile,line))
        {
            j=0;
            // words.clear();
            sin.clear();
            sin.str(line);
            // 将字符串流sin中的字符读到字符串数组words中，以逗号为分隔符
            while(getline(sin,word,','))
            {
                // cout<<word<<endl;
                words.push_back(word);
                ihl0_input[i][j]=static_cast<int>(strtol(word.c_str(),&end,10));              //string -> int
                j++;
            }
            // cout<<endl;
            i++;
        }
        inFile.close();
    }  
}
void compute_params::read_ihl0_weight()
{
    ifstream inFile("/home/ashlyn/Documents/SNARK/libsnark_abc/src/data/ihl0_weight_fixed.csv", ios::in);
    string lineStr;  
    vector<vector<string>> strArray;  
    int i,j;
    i=0;
    char* end;
    // cout<<"ihl0_weight"<<endl<<endl;
    if(inFile.fail())
        cout<<"读取文件失败"<<endl;

    else
    {
        string line;
        vector<string>words;
        string word;
        // 读取标题行
        // getline(inFile,line);
        istringstream sin;
        // 按行读取数据
        while(getline(inFile,line))
        {
            j=0;
            // words.clear();
            sin.clear();
            sin.str(line);
            // 将字符串流sin中的字符读到字符串数组words中，以逗号为分隔符
            while(getline(sin,word,','))
            {
                // cout<<word<<endl;
                words.push_back(word);
                ihl0_weight[i][j]=static_cast<int>(strtol(word.c_str(),&end,10));              //string -> int
                j++;
            }
            i++;
        }
        inFile.close();
    }
}
void compute_params::read_ihl0_bias()
{
    ifstream inFile("/home/ashlyn/Documents/SNARK/libsnark_abc/src/data/ihl0_bias_fixed.csv", ios::in);
    string lineStr;  
    vector<vector<string>> strArray;  
    int i,j;
    i=0;
    char* end;
    // cout<<"ihl0_bias"<<endl<<endl;
    if(inFile.fail())
        cout<<"读取文件失败"<<endl;

    else
    {
        string line;
        vector<string>words;
        string word;
        // 读取标题行
        // getline(inFile,line);
        istringstream sin;
        // 按行读取数据
        while(getline(inFile,line))
        {
            // words.clear();
            sin.clear();
            sin.str(line);
            // 将字符串流sin中的字符读到字符串数组words中，以逗号为分隔符
            while(getline(sin,word,','))
            {
                // cout<<word<<endl;
                words.push_back(word);
                ihl0_bias[i]=static_cast<int>(strtol(word.c_str(),&end,10));              //string -> int
            }
            i++;
        }
        inFile.close();
    }
}
void compute_params::weight_encoded_query()
{
    // 行列索引
    int row=0,column=0;
}
void compute_params::weightMulinput()//计算weight*input的结果,保存为sys1
{
    // 先将输入矩阵input转置
    int temp;
    for(int i=0;i<4*hidden_size;i++)
    {
        for(int j=0;j<input_size;j++)
        {
            ihl0_input_T[j][i] = ihl0_input[i][j];
        }
    }
    for(int i=0;i<4*hidden_size;i++)
    {
        for(int j=0;j<4*hidden_size;j++)
        {
            for(int m=0;m<input_size;m++)
            {
                ihl0_sys1[i][j]+=ihl0_weight[i][m]*ihl0_input_T[m][j];
            }
        }
    }
}
void compute_params::sysAddbias()//计算weight*input的结果+bias
{
    for(int i=0;i<4*hidden_size;i++)
    {
        for(int j=0;j<4*hidden_size;j++)
        {
            ihl0_out[i][j]=ihl0_sys1[i][j]+ihl0_bias[j];
        }
    }
    cout<<endl;
}
void compute_params::getsys11()//计算weight*input矩阵元素两两相乘的中间变量
{
    for (int i = 0; i < 4*hidden_size; i++)
    {
        for (int j = 0; j < 4*hidden_size; j++)
        {
            for (int k = 0; k < input_size; k++)
            {
                ihl0_sys11[i][j*input_size+k]=ihl0_weight[i][k]*ihl0_input[j][k];
            }
            
        }
    }
}
void compute_params::getsys12()// 矩阵乘法A*B=C,A的行元素A[0][-1]和B的列元素B[-1][0]乘积的和，作为C的结果C[0][0],对每两个和生成对应的中间变量
{
    for (int i = 0; i < 4*hidden_size; i++)
    {
        for (int j = 0; j < 4*hidden_size; j++)
        {
            for (int k = 0; k < input_size; k++)
            {
                if (k==0)
                {
                    ihl0_sys12[i][j*input_size+k] = ihl0_sys11[i][j*input_size+k]+ihl0_sys11[i][j*input_size+k+1];
                }
                else
                {
                    ihl0_sys12[i][j*input_size+k] = ihl0_sys11[i][j*input_size+k+1]+ihl0_sys12[i][j*input_size+k-1];
                }
            }
            
        }
    }
}
int main()
{
    // 加载各个矩阵的值
    compute_params params;
    params.read_ihl0_input();
    params.read_ihl0_weight();
    params.read_ihl0_bias();
    // params.read_ihl0_output();
    params.weightMulinput();
    params.sysAddbias();
    params.getsys11();
    params.getsys12();

    // Initialize the curve parameters
    cout<<"Initialize the curve parameters"<<endl;
    typedef libff::Fr<default_r1cs_gg_ppzksnark_pp> FieldT;
    default_r1cs_gg_ppzksnark_pp::init_public_params();


    // Create protoboard
    static protoboard<FieldT> pb;

    // Define variables
    static pb_variable<FieldT> pb_weight[4*20][10];
    static pb_variable<FieldT> pb_input[4*20][10];
    static pb_variable<FieldT> pv_bias[4*20];
    static pb_variable<FieldT> pb_sys1[4*20][4*20];
    static pb_variable<FieldT> pb_out[4*20][4*20];
    static pb_variable<FieldT> pb_sys11[4*20][10*4*20];
    static pb_variable<FieldT> pb_sys12[4*20][9*80];
    static pb_variable<FieldT> pb_weight_encoded_indexed[4*20*10];
    static pb_variable<FieldT> pb_encode_row[80];
    static pb_variable<FieldT> pb_encode_column[10];
    static pb_variable<FieldT> pb_index_encoded[4*20*10];


    // //base
    // // 公共变量连接
    // // 变量pb_sys2(+bias后的结果,ihl0层的输出)与protoboard连接
    // for(int i=0;i<4*hidden_size;i++)
    // {
    //     for(int j=0;j<4*hidden_size;j++)
    //     {
    //         string pi = "sys2"+to_string(i)+" "+to_string(j);
    //         pb_out[i][j].allocate(pb, pi);
    //         pb.val(pb_out[i][j])=ihl0_out[i][j];
    //     }
    // }
    // // 私有变量连接
    // // 变量pb_weight与protoboard连接
    // for(int i=0;i<4*hidden_size;i++)
    // {
    //     for(int j=0;j<input_size;j++)
    //     {
    //         string pi = "weight"+to_string(i)+" "+to_string(j);
    //         pb_weight[i][j].allocate(pb, pi);
    //         pb.val(pb_weight[i][j])=ihl0_weight[i][j];
    //     }
    // }
    // // 变量pb_input与protoboard连接
    // for(int i=0;i<4*hidden_size;i++)
    // {
    //     for(int j=0;j<input_size;j++)
    //     {
    //         string pi = "weight"+to_string(i)+" "+to_string(j);
    //         pb_input[i][j].allocate(pb, pi);
    //         pb.val(pb_input[i][j])=ihl0_input[i][j];
    //     }
    // }
    // // weight*input的结果sys1与protoboard连接
    // for(int i=0;i<4*hidden_size;i++)
    // {
    //     for(int j=0;j<4*hidden_size;j++)
    //     {
    //         string pi = "weight*input"+to_string(i)+" "+to_string(j);
    //         pb_sys1[i][j].allocate(pb, pi);
    //         pb.val(pb_sys1[i][j])=ihl0_sys1[i][j];
    //     }
    // }
    // // weight*input矩阵元素两两相乘的中间变量sys11与protoboard连接
    // for ( int i = 0; i < 4*hidden_size; i++ )
    // {   
    //     for(int j = 0; j < 4*hidden_size*input_size; j++)
    //     {
    //         std::string pi = "Sym11_" + std::to_string(i)+"_"+std::to_string(j); 
    //         pb_sys11[i][j].allocate(pb,pi);
    //         pb.val(pb_sys11[i][j]) = ihl0_sys11[i][j]; 
    //     }
    // }
    // // 每两个和生成对应的中间变量sys12与protoboard连接
    // for ( int i = 0; i < 4*hidden_size; i++ )
    // {   
    //     for(int j = 0; j < 9*4*hidden_size; j++)
    //     {
    //         std::string pi = "Sym12_add" + std::to_string(i)+"_"+std::to_string(j); 
    //         pb_sys12[i][j].allocate(pb,pi);
    //         pb.val(pb_sys12[i][j]) = ihl0_sys12[i][j]; 
    //     }
    // }
    // // 偏置量与protoboard连接
    // for(int i=0;i<4*hidden_size;i++)
    // {
    //     string pi = "bias"+to_string(i)+" "+to_string(i);
    //     pv_bias[i].allocate(pb, pi);
    //     pb.val(pv_bias[i])=ihl0_bias[i];
    // }

    // // input and the rest is private input,public num first 6480
    // pb.set_input_sizes(6400);

    // // Add R1CS constraints to protoboard
    // // weight*input
    // for (int i = 0; i < 4*hidden_size; i++)
    // {
    //     for (int j = 0; j < 4*hidden_size; j++)
    //     {
    //         for (int k = 0; k < input_size; k++)
    //         {
    //             pb.add_r1cs_constraint(r1cs_constraint<FieldT>(pb_weight[i][k], pb_input[j][k], pb_sys11[i][j*input_size+k]));
    //         }
            
    //     }
    // }
    // // weight*input形成的中间变量求和
    // for (int i = 0; i < 4*hidden_size; i++)
    // {
    //     for (int j = 0; j < 4*hidden_size; j++)
    //     {
    //         for (int k = 0; k < input_size -1; k++)
    //         {
    //             if (k==0)
    //             {
    //                 pb.add_r1cs_constraint(r1cs_constraint<FieldT>(pb_sys11[i][j*4*hidden_size+k]+pb_sys11[i][j*4*hidden_size+k+1], 1, pb_sys12[i][j*4*hidden_size+k]));
    //             }
    //             else
    //             {
    //                 pb.add_r1cs_constraint(r1cs_constraint<FieldT>(pb_sys12[i][j*4*hidden_size+k-1]+pb_sys11[i][j*4*hidden_size+k+1], 1, pb_sys12[i][j*4*hidden_size+k]));
    //             }
    //         }
            
    //     }
    // }
    // // weight*input+bias
    // for (int i = 0; i < 4*hidden_size; i++)
    // {
    //     for (int j = 0; j < 4*hidden_size; j++)
    //     {
    //         pb.add_r1cs_constraint(r1cs_constraint<FieldT>(pb_sys12[i][j*input_size+input_size-2]+pv_bias[j], 1, pb_out[i][j]));
    //     }
    // }
    // const r1cs_constraint_system<FieldT> constraint_system = pb.get_constraint_system();

    // struct timeval startSetup,EndSetup,startGenProof,EndGenProof,startVerify,EndVerify;
    // unsigned long setupTime,proofTime,verifyTime;

    // // generate keypair
    // gettimeofday(&startSetup,NULL);
    // const r1cs_gg_ppzksnark_keypair<default_r1cs_gg_ppzksnark_pp> keypair = r1cs_gg_ppzksnark_generator<default_r1cs_gg_ppzksnark_pp>(constraint_system);
    // gettimeofday(&EndSetup,NULL);
    
    // // generate proof
    // gettimeofday(&startGenProof,NULL);
    // const r1cs_gg_ppzksnark_proof<default_r1cs_gg_ppzksnark_pp> proof = r1cs_gg_ppzksnark_prover<default_r1cs_gg_ppzksnark_pp>(keypair.pk, pb.primary_input(), pb.auxiliary_input());
    // gettimeofday(&EndGenProof,NULL);

    // // verify
    // gettimeofday(&startVerify,NULL);
    // bool verified = r1cs_gg_ppzksnark_verifier_strong_IC<default_r1cs_gg_ppzksnark_pp>(keypair.vk, pb.primary_input(), proof);
    // gettimeofday(&EndVerify,NULL);

    // cout<<"base scheme---"<<endl;
    // cout << "Number of R1CS constraints: " << constraint_system.num_constraints() << endl;
    // // cout << "Primary (public) input: " << pb.primary_input() << endl;
    // // cout << "Auxiliary (private) input: " << pb.auxiliary_input() << endl;
    // cout << "Verification status: " << verified << endl;

    // setupTime = 1000000 * (EndSetup.tv_sec-startSetup.tv_sec)+EndSetup.tv_usec-startSetup.tv_usec;
    // proofTime = 1000000 * (EndGenProof.tv_sec-startGenProof.tv_sec)+EndGenProof.tv_usec-startGenProof.tv_usec;
    // verifyTime = 1000000* (EndVerify.tv_sec-startVerify.tv_sec)+EndVerify.tv_usec-startVerify.tv_usec;
    // cout<<"setup time(ms):"<<setupTime/1000<<endl;
    // cout<<"proof time(ms):"<<proofTime/1000<<endl;
    // cout<<"verift time(ms):"<<verifyTime/1000<<endl;




    // encoded scheme

    // // 权重矩阵中的每个权重用row，column表示
    // for(int i=0;i<4*hidden_size;i++)
    // {
    //     for(int j=0;j<input_size;j++)
    //     {
    //         encode_row[i] = i;
    //         encode_column[j] = j;
    //     }
    // }
    // 将ihl0_weight每个权重以编码表示，即将weight矩阵拍平，用ihl0_weight_indexed表示拍平后的索引值
    for(int i=0;i<4*hidden_size;i++)
    {
        for(int j=0;j<input_size;j++)
        {
            weight_encoded_indexed[i*input_size + j] = i*input_size + j;
        }
    }
    // row,column->index_encoded
    for(int i=0;i<4*hidden_size;i++)
    {
        for(int j=0;j<input_size;j++)
        {
            index_encoded[i*input_size+j] = i*input_size+j;
        }
    }
    
    // 公共变量连接
    // 变量pb_sys2(+bias后的结果,ihl0层的输出)与protoboard连接
    for(int i=0;i<4*hidden_size;i++)
    {
        for(int j=0;j<4*hidden_size;j++)
        {
            string pi = "sys2"+to_string(i)+" "+to_string(j);
            pb_out[i][j].allocate(pb, pi);
            pb.val(pb_out[i][j])=ihl0_out[i][j];
        }
    }
    cout<<"test1"<<endl;
    // 私有变量连接

    // // 索引row，column与protoboard连接
    // for (int i = 0; i < 4*hidden_size; i++)
    // {
    //     string pi = "weight_index_row"+to_string(i)+" ";
    //     pb_encode_row[i].allocate(pb, pi);
    //     pb_encoded.val(pb_encode_row[i])=encode_row[i];
    // }
    // for (int i = 0; i <input_size; i++)
    // {
    //     string pi = "weight_index_column"+to_string(i)+" ";
    //     pb_encode_column[i].allocate(pb, pi);
    //     pb_encoded.val(pb_encode_column[i])=encode_column[i];
    // }
    for (int i = 0; i < 4*hidden_size*input_size; i++)
    {
        string pi = "index_encoded"+to_string(i);
        pb_index_encoded[i].allocate(pb, pi);
        pb.val(pb_index_encoded[i])=index_encoded[i];
    }
    cout<<"test2"<<endl;

    // 拍平后的weight的索引值encoded index与protoboard连接
    for (int i = 0; i < 4*hidden_size*input_size; i++)
    {
        string pi = "weight_encoed_index"+to_string(i);
        pb_weight_encoded_indexed[i].allocate(pb, pi);
        pb.val(pb_weight_encoded_indexed[i])=weight_encoded_indexed[i];
    }
      cout<<"test1--"<<endl;
    // 变量pb_input与protoboard连接
    for(int i=0;i<4*hidden_size;i++)
    {
        for(int j=0;j<input_size;j++)
        {
            string pi = "weight"+to_string(i)+" "+to_string(j);
            pb_input[i][j].allocate(pb, pi);
            pb.val(pb_input[i][j])=ihl0_input[i][j];
        }
    }
    cout<<"test1---"<<endl;
    // weight*input的结果sys1与protoboard连接
    for(int i=0;i<4*hidden_size;i++)
    {
        for(int j=0;j<4*hidden_size;j++)
        {
            string pi = "weight*input"+to_string(i)+" "+to_string(j);
            pb_sys1[i][j].allocate(pb, pi);
            pb.val(pb_sys1[i][j])=ihl0_sys1[i][j];
        }
    }
    cout<<"test1----"<<endl;
    // weight*input矩阵元素两两相乘的中间变量sys11与protoboard连接
    for ( int i = 0; i < 4*hidden_size; i++ )
    {   
        for(int j = 0; j < 4*hidden_size*input_size; j++)
        {
            string pi = "Sym11_" + std::to_string(i)+"_"+std::to_string(j); 
            pb_sys11[i][j].allocate(pb,pi);
            pb.val(pb_sys11[i][j]) = ihl0_sys11[i][j]; 
        }
    }
    // 每两个和生成对应的中间变量sys12与protoboard连接
    for ( int i = 0; i < 4*hidden_size; i++ )
    {   
        for(int j = 0; j < 9*4*hidden_size; j++)
        {
            std::string pi = "Sym12_add" + std::to_string(i)+"_"+std::to_string(j); 
            pb_sys12[i][j].allocate(pb,pi);
            pb.val(pb_sys12[i][j]) = ihl0_sys12[i][j]; 
        }
    }
    // 偏置量与protoboard连接
    for(int i=0;i<4*hidden_size;i++)
    {
        string pi = "bias"+to_string(i)+" "+to_string(i);
        pv_bias[i].allocate(pb, pi);
        pb.val(pv_bias[i])=ihl0_bias[i];
    }

    // input and the rest is private input,public num first 6480
    pb.set_input_sizes(6400);
    cout<<"set inputsize"<<endl;

    // Add R1CS constraints to protoboard
    // 索引查询weight的约束
    // for (int i = 0; i < 4*hidden_size; i++)
    // {
    //     for (int j = 0; j < input_size; j++)
    //     {
    //         pb_encoded.add_r1cs_constraint(r1cs_constraint<FieldT>(pb_encode_row[i]*10+pb_encode_column[j], 1, pb_weight_encoded_indexed[i][j]));
    //     }   
    // }
    for (int j = 0; j < 4*hidden_size*input_size; j++)
    {
        pb.add_r1cs_constraint(r1cs_constraint<FieldT>(pb_index_encoded[j], 1, pb_weight_encoded_indexed[j]));
    }   

    
    
    // weight*input形成的中间变量求和
    for (int i = 0; i < 4*hidden_size; i++)
    {
        for (int j = 0; j < 4*hidden_size; j++)
        {
            for (int k = 0; k < input_size -1; k++)
            {
                if (k==0)
                {
                    pb.add_r1cs_constraint(r1cs_constraint<FieldT>(pb_sys11[i][j*4*hidden_size+k]+pb_sys11[i][j*4*hidden_size+k+1], 1, pb_sys12[i][j*4*hidden_size+k]));
                }
                else
                {
                    pb.add_r1cs_constraint(r1cs_constraint<FieldT>(pb_sys12[i][j*4*hidden_size+k-1]+pb_sys11[i][j*4*hidden_size+k+1], 1, pb_sys12[i][j*4*hidden_size+k]));
                }
            }
            
        }
    }
    // weight*input+bias
    for (int i = 0; i < 4*hidden_size; i++)
    {
        for (int j = 0; j < 4*hidden_size; j++)
        {
            pb.add_r1cs_constraint(r1cs_constraint<FieldT>(pb_sys12[i][j*input_size+input_size-2]+pv_bias[j], 1, pb_out[i][j]));
        }
    }

    const r1cs_constraint_system<FieldT> constraint_system = pb.get_constraint_system();

    struct timeval startSetup,EndSetup,startGenProof,EndGenProof,startVerify,EndVerify;
    unsigned long setupTime,proofTime,verifyTime;
    

    // generate keypair
    gettimeofday(&startSetup,NULL);
    const r1cs_gg_ppzksnark_keypair<default_r1cs_gg_ppzksnark_pp> keypair= r1cs_gg_ppzksnark_generator<default_r1cs_gg_ppzksnark_pp>(constraint_system);
    gettimeofday(&EndSetup,NULL);
    
    // generate proof
    gettimeofday(&startGenProof,NULL);
    const r1cs_gg_ppzksnark_proof<default_r1cs_gg_ppzksnark_pp> proof = r1cs_gg_ppzksnark_prover<default_r1cs_gg_ppzksnark_pp>(keypair.pk, pb.primary_input(), pb.auxiliary_input());
    gettimeofday(&EndGenProof,NULL);

    // verify
    gettimeofday(&startVerify,NULL);
    bool verified = r1cs_gg_ppzksnark_verifier_strong_IC<default_r1cs_gg_ppzksnark_pp>(keypair.vk, pb.primary_input(), proof);
    gettimeofday(&EndVerify,NULL);

    cout<<"encoded scheme---"<<endl;
    cout << "Number of R1CS constraints: " << constraint_system.num_constraints() << endl;
    // cout << "Primary (public) input: " << pb.primary_input() << endl;
    // cout << "Auxiliary (private) input: " << pb.auxiliary_input() << endl;
    cout << "Verification status: " << verified << endl;

    setupTime = 1000000 * (EndSetup.tv_sec-startSetup.tv_sec)+EndSetup.tv_usec-startSetup.tv_usec;
    proofTime = 1000000 * (EndGenProof.tv_sec-startGenProof.tv_sec)+EndGenProof.tv_usec-startGenProof.tv_usec;
    verifyTime = 1000000 * (EndVerify.tv_sec-startVerify.tv_sec)+EndVerify.tv_usec-startVerify.tv_usec;
    cout<<"setup time_en(ms):"<<setupTime/1000<<endl;
    cout<<"proof time_en(ms):"<<proofTime/1000<<endl;
    cout<<"verift time_en(ms):"<<verifyTime/1000<<endl;
    
}