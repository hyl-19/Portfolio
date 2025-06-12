import os
from dotenv import load_dotenv
from openai import OpenAI
import tiktoken
import boto3
from sentence_transformers import SentenceTransformer
import faiss

# Load .env
load_dotenv('test.env')

# Constants
MAX_TOKENS = 1000
TOP_K      = 3

# OpenAI 客戶端 & tokenizer
openai_client = OpenAI(api_key=os.getenv("OPENAI_API_KEY"))
tokenizer     = tiktoken.encoding_for_model("gpt-4o-mini")

# Embedding model
embedder = SentenceTransformer('all-MiniLM-L6-v2')

# AWS clients
aws_region = os.getenv('AWS_REGION','us-east-1')
s3         = boto3.client('s3',      region_name=aws_region)
textract   = boto3.client('textract',region_name=aws_region)
dynamodb   = boto3.resource('dynamodb',region_name=aws_region)
ddb_table  = dynamodb.Table(os.environ['DDB_TABLE_NAME'])

UPLOAD_STATUS = {}