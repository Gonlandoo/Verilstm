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
#include <libsnark/common/default_types/r1cs_gg_ppzksnark_pp.hpp>
#include <libsnark/zk_proof_systems/ppzksnark/r1cs_gg_ppzksnark/r1cs_gg_ppzksnark.hpp>
#include <libsnark/gadgetlib1/pb_variable.hpp>

using namespace libsnark;

static int hidden_size = 20;
static int input_size = 10;
static int ihl0_input[4*20][10];
static int ihl0_input_T[10][4*20];
static int ihl0_weight[4*20][10];
static int ihl0_bias[4*20];
static int ihl0_output[4*20][20];
static int ihl0_sys1[4*20][4*20];
static int ihl0_out[4*20][4*20];
static int Freivalds_r[4*20];
static int vMulr_sys[10];
static int wInMulr_sys[4*20];
static int wInMulr[4*20];
static int ihl0_sys11[4*20][10*4*20];
static int ihl0_sys12[4*20][9*4*20];


// pb_variable<FieldT>ihl0Sym1_var[4*20][4*20];
// pb_variable<FieldT>ihl0Sym_var[4*20][4*20];
// pb_variable<FieldT>ihl0Sym2_var[4*20][4*20];

class read_params
{
   public:
      void read_ihl0_input();
      void read_ihl0_weight();
      void read_ihl0_bias();
      void read_ihl0_output();
      void weight_encoded_query(); 
      void weightMulinput();
      void sysAddbias();
      void vMulr();
      void wMulr();
      void wMulvMulr();
};
void read_params::read_ihl0_input()
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
                // cout<<ihl0_input[i][j]<<" ";
                // cout<<"i,j="<<i<<j<<endl;
                j++;
            }
            // cout<<endl;
            i++;
        }
        // for(int i=0;i<80;i++)
        // {
        //     for(int j=0;j<10;j++)
        //         cout<<"i,j:"<<i<<","<<j<<" "<<arr_ihl0_input[i][j]<<" ";
        //     // cout<<"i,j:"<<i<<","<<j<<endl;
        //     cout<<endl;
        // }
        inFile.close();
    }  
}
void read_params::read_ihl0_weight()
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
                // cout<<arr_ihl0_weight[i][j]<<" ";
                // cout<<"i,j="<<i<<j<<endl;
                j++;
            }
            // cout<<endl;
            i++;
        }
        // for(int i=0;i<80;i++)
        // {
        //     for(int j=0;j<10;j++)
        //         cout<<"i,j:"<<i<<","<<j<<" "<<arr_ihl0_weight[i][j]<<" ";
        //     // cout<<"i,j:"<<i<<","<<j<<endl;
        //     cout<<endl;
        // }
        inFile.close();
    }
}
void read_params::read_ihl0_bias()
{
    ifstream inFile("/home/ashlyn/Documents/SNARK/libsnark_abc/src/data/ihl0_bias_fixed.csv", ios::in);
    string lineStr;  
    vector<vector<string>> strArray;  
    int i;
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
                // cout<<arr_ihl0_bias[i]<<" ";
                // cout<<"i="<<i<<endl;
            }
            // cout<<endl;
            i++;
        }
        // for(int i=0;i<80;i++)
        // {
        //     cout<<"i"<<i<<" "<<arr_ihl0_bias[i]<<" ";
        // }
        inFile.close();
    }
}
void read_params::read_ihl0_output()
{
    ifstream inFile("/home/ashlyn/Documents/SNARK/libsnark_abc/src/data/l0_output_fixed_reshaped.csv", ios::in);
    string lineStr;  
    vector<vector<string>> strArray;  
    int i,j;
    i=0;
    char* end;
    // cout<<"ihl0_output"<<endl<<endl;
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
                ihl0_output[i][j]=static_cast<int>(strtol(word.c_str(),&end,10));              //string -> int
                // cout<<arr_ihl0_output[i][j]<<" ";
                // cout<<"i,j="<<i<<j<<endl;
                j++;
            }
            // cout<<endl;
            i++;
        }
        // for(int i=0;i<80;i++)
        // {
        //     for(int j=0;j<20;j++)
        //         cout<<"i,j:"<<i<<","<<j<<" "<<arr_ihl0_output[i][j]<<" ";
        //     // cout<<"i,j:"<<i<<","<<j<<endl;
        //     cout<<endl;
        // }
        inFile.close();
    }
}
void read_params::weight_encoded_query()
{
    // 行列索引
    int row=0,column=0;
}
void read_params::weightMulinput()
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
    // for(int i=0;i<4*hidden_size;i++)
    // {
    //     for(int j=0;j<4*hidden_size;j++)
    //     {
    //         cout<<"i,j"<<i<<j<<" "<<ihl0_sys1[i][j];
    //     }
    //     cout<<endl;
    // }
}
void read_params::sysAddbias()
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
void read_params::vMulr()
{
    for(int i=0;i<input_size;i++)
    {
        for(int j=0;j<4*hidden_size;j++)
            vMulr_sys[i]+=Freivalds_r[j]*ihl0_input[i][j];
    }
}
void read_params::wMulr()
{
    for(int i=0;i<4*hidden_size;i++)
    {
        for(int j=0;j<input_size;j++)
            wInMulr_sys[i]+=Freivalds_r[j]*ihl0_weight[i][j];
    }
}
void read_params::wMulvMulr()
{
    for(int i=0;i<4*hidden_size;i++)
    {
        for(int j=0;j<4*hidden_size;j++)
        {
            wInMulr[i]+=ihl0_sys1[i][j]*Freivalds_r[j];
        }
    }
}
int main()
{
    typedef libff::Fr<default_r1cs_gg_ppzksnark_pp> FieldT;
    // Initialize the curve parameters
    default_r1cs_gg_ppzksnark_pp::init_public_params();
    // 生成Freivalds_r随机向量
    for(int i=0;i<4*hidden_size;i++)
    {
        Freivalds_r[i]=rand()%10;
    }
    // 加载各个矩阵的值
    read_params read;
    read.read_ihl0_input();
    read.read_ihl0_weight();
    read.read_ihl0_bias();
    // read.read_ihl0_output();
    read.weightMulinput();
    read.sysAddbias();
    // read.vMulr();
    // read.wMulr();
    // read.wMulvMulr();

    

    // Initialize the curve parameters
    default_r1cs_gg_ppzksnark_pp::init_public_params();
  
    // Create protoboard
    protoboard<FieldT> pb;

    // Define variables
    pb_variable<FieldT> pb_weight[4*20][10];
    pb_variable<FieldT> pb_input[4*20][10];
    pb_variable<FieldT> pv_bias[4*20];
    pb_variable<FieldT> pb_sys1[4*20][4*20];
    pb_variable<FieldT> pb_out[4*20][4*20];
    pb_variable<FieldT> pb_Freivalds_r[4*20];
    pb_variable<FieldT> pb_vMulr[4*20];
    pb_variable<FieldT> pb_vInMulr_sys[4*20];
    pb_variable<FieldT> pb_wInMulr[4*20];
    pb_variable<FieldT> pb_sys11[4*20][10*4*20];
    pb_variable<FieldT> pb_sys12[4*20][9*80];

    cout<<"initialize completed"<<endl;

    // 计算weight*input矩阵所有元素两两相乘的中间变量
    for (int i = 0; i < 4*hidden_size; i++)
    {
        for(int j =0 ;j<4*hidden_size ;j++)
        {
            for (int k = 0; k < input_size; k++)
            {
                ihl0_sys11[i][j * input_size + k]=ihl0_weight[i][k]*ihl0_input[j][k];
            }
        }
        
    }

    // for(int i=0;i<4*hidden_size;i++)
    // {
    //     for(int j=0;j<input_size;j++)
    //     {
    //         cout<<"sys11_"<<i<<j<<" "<<ihl0_sys11[i][j];
    //     }
    // }
    
    // 矩阵乘法A*B=C,A的行元素A[0][-1]和B的列元素B[-1][0]乘积的和，作为C的结果C[0][0],对每两个和生成对应的中间变量
    for (int i = 0; i < 4*hidden_size; i++)
    {
        for (int j = 0; j < 4*hidden_size; j++)
        {
            for(int k=0;k<input_size-1;k++)
            {
                if (k==0)
                {
                    ihl0_sys12[i][j * input_size + k]=ihl0_sys11[i][j * input_size + k]+ihl0_sys11[i][j * input_size + k +1];
                }
                else
                {
                    ihl0_sys12[i][j * input_size + k]=ihl0_sys11[i][j * input_size + k +1]+ihl0_sys12[i][j * input_size + k-1];
                }
            }
            
        }
    }
    // for (int i = 0; i < 4*hidden_size; i++)
    // {
    //     for (int j = 0; j < 9; j++)
    //     {
    //         cout<<"sys12"<<ihl0_sys12[i][j];
    //     }
    //     cout<<endl;
    // }

    // Allocate variables to protoboard
    // The strings (like "x") are only for debugging purposes
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

    // 私有变量的连接
    // 变量pb_weight与protoboard连接
    for(int i=0;i<4*hidden_size;i++)
    {
        for(int j=0;j<input_size;j++)
        {
            string pi = "weight"+to_string(i)+" "+to_string(j);
            pb_weight[i][j].allocate(pb, pi);
            pb.val(pb_weight[i][j])=ihl0_weight[i][j];
        }
    }

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

    // weight*input的结果与protoboard连接
    for(int i=0;i<4*hidden_size;i++)
    {
        for(int j=0;j<4*hidden_size;j++)
        {
            string pi = "weight*input"+to_string(i)+" "+to_string(j);
            pb_sys1[i][j].allocate(pb, pi);
            pb.val(pb_sys1[i][j])=ihl0_sys1[i][j];
        }
    }
    
    for ( int i = 0; i < 4*hidden_size; i++ )
    {   
        for(int j = 0; j < 4*hidden_size * input_size; j++)
        {
            std::string pi = "Sym11_" + std::to_string(i)+"_"+std::to_string(j); 
            pb_sys11[i][j].allocate(pb,pi);
            pb.val(pb_sys11[i][j]) = ihl0_sys11[i][j]; 
        }
    }
    
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
    cout<<"set_input size"<<endl;
    pb.set_input_sizes(6400);

    // Add R1CS constraints to protoboard

    //weigt*input
    for (int i = 0; i < 4*hidden_size; i++)
    {
        for(int j =0 ;j<4*hidden_size ;j++)
        {
            for (int k = 0; k < input_size; k++)
            {
                ihl0_sys11[i][j * input_size + k]=ihl0_weight[i][k]*ihl0_input[j][k];
                // pb.add_r1cs_constraint(r1cs_constraint<FieldT>(pb_weight[i][k], pb_input[j][k], pb_sys1[i][j * input_size + k]));
                pb.add_r1cs_constraint(r1cs_constraint<FieldT>(pb_weight[i][k], pb_input[j][k], pb_sys1[i][j * input_size + k]));
            }
        }
        
    }

    // // weight*input形成的中间变量求和
    // for (int i = 0; i < 4*hidden_size; i++)
    // {
    //     for (int j = 0; j < 4*hidden_size; j++)
    //     {
    //         for(int k=0;k<input_size-1;k++)
    //         {
    //             if (k==0)
    //             {
    //                 pb.add_r1cs_constraint(r1cs_constraint<FieldT>(pb_sys11[i][j * input_size + k]+pb_sys11[i][j * input_size + k +1], 1, pb_sys12[i][j*input_size+k]));
    //             }
    //             else
    //             {
    //                 pb.add_r1cs_constraint(r1cs_constraint<FieldT>(pb_sys12[i][j * input_size + k-1]+pb_sys11[i][j*input_size + k +1], 1, pb_sys12[i][j * input_size + k]));
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

    struct timeval startSetup,EndSetup,startGenProof,EndGenProof,StartVerify,EndVerify;
    unsigned long setupTime,proofTime,verifyTime;
    
    const r1cs_constraint_system<FieldT> constraint_system = pb.get_constraint_system();

    // generate keypair
    gettimeofday(&startSetup,NULL);
    const r1cs_gg_ppzksnark_keypair<default_r1cs_gg_ppzksnark_pp> keypair = r1cs_gg_ppzksnark_generator<default_r1cs_gg_ppzksnark_pp>(constraint_system);
    gettimeofday(&EndSetup,NULL);
    
    // generate proof
    // gettimeofday(&startGenProof,NULL);
    const r1cs_gg_ppzksnark_proof<default_r1cs_gg_ppzksnark_pp> proof = r1cs_gg_ppzksnark_prover<default_r1cs_gg_ppzksnark_pp>(keypair.pk, pb.primary_input(), pb.auxiliary_input());
    // gettimeofday(&EndGenProof,NULL);

    // verify
    // gettimeofday(&StartVerify,NULL);
    bool verified = r1cs_gg_ppzksnark_verifier_strong_IC<default_r1cs_gg_ppzksnark_pp>(keypair.vk, pb.primary_input(), proof);
    // gettimeofday(&EndVerify,NULL);

    cout << "Number of R1CS constraints: " << constraint_system.num_constraints() << endl;
    // cout << "Primary (public) input: " << pb.primary_input() << endl;
    // cout << "Auxiliary (private) input: " << pb.auxiliary_input() << endl;
    cout << "Verification status: " << verified << endl;

    setupTime = 1000000 * (EndSetup.tv_sec-startSetup.tv_sec)+EndSetup.tv_usec-startSetup.tv_usec;
    cout<<"setup time:"<<setupTime/1000;

}
