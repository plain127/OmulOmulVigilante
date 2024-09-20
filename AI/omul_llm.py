import os
import openai
from langchain.chat_models import ChatOpenAI
from langchain.document_loaders import TextLoader
from langchain.text_splitter import RecursiveCharacterTextSplitter
from langchain.embeddings import OpenAIEmbeddings
from langchain.vectorstores import Chroma
from langchain.prompts import ChatPromptTemplate, HumanMessagePromptTemplate, SystemMessagePromptTemplate
from langchain.chains import LLMChain

class OmulLLM:
    def __init__(self, action_result, data_path):
        self.action_result = action_result
        self.document_path = data_path
        
        #.env파일에 있는 openai api key를 호출 
        os.environ['OPENAI_API_KEY'] = 'Input Your OpenAI API Key'
        self.llm_model = ChatOpenAI(model_name='gpt-4o-mini', temperature=0.5)
        self.llm_prompt = None
        self.chat_chain = None
        self.score = None
        self.reason = None
        
    def load_document(self):
        loader = TextLoader(self.document_path, encoding='utf-8')
        document = loader.load()
        return document
    
    def embedding_txt(self, document):
        embeddings = OpenAIEmbeddings()
        embeddings.embed_documents(document[0].page_content)
        return embeddings
    
    def split_document(self, document):
        text_splitter = RecursiveCharacterTextSplitter(separators=['\n\n', '\n'], chunk_size=100, chunk_overlap=50)
        docs = text_splitter.create_documents([document[0].page_content])
        return docs

    def create_vectordb(self):
        if os.path.exists('omulDB'):
            vectordb = Chroma(persist_directory='omulDB')
            retriver = vectordb.as_retriever()
        else:
            document = self.load_document()
            embeddings = self.embedding_txt(document)
            docs = self.split_document(document)
            persist_directory = 'omulDB'
            vectordb = Chroma.from_documents(
                documents=docs,
                embedding=embeddings,
                persist_directory=persist_directory
            )
            vectordb.persist()
            retriver = vectordb.as_retriever()
        
        return retriver
        
    def prompt_engineering(self):
        retriver = self.create_vectordb()
        rag_prompt = f'{retriver}는 오물풍선 대응 및 대처 매뉴얼이야. 특정 값들이 입력되면 {retriver}에 있는 정보를 바탕으로 오물풍선의 개념, 대처법을 추론해서 점수를 생성할때 반영해'
        judge_prompt = '''
            넌 대한민국의 테러 대응 대책본부에서 근무하는 북한 "오물풍선" 대처 훈련의 최고전문가이자 교관이야. 
            민간인인 시민 훈련생이 오물풍선을 발견했을때, 오물풍선에 접촉하지 말아야하는 반경 허용거리(cm 단위야), 
            오물풍선 발견을 관련기관에 신고하는 내용, 오물풍선 발견시 위험을 인지하고 물체에 접근하지 않도록 주변 사람들에게 알렸다는 True, False 내용이
            인풋으로 들어오면 그 사람의 행동이 적절했는지 판단해서 첫째 줄에 10에서 100점 사이의 점수를 오직 숫자로만 나오게해.
            둘째 줄에 다른 서술은 다 제외하고 그 점수를 산출한 이유를 이야기해.
            이유는 150자 이내로 작성해.
        '''
        llm_prompt = ChatPromptTemplate.from_messages(
            [
                SystemMessagePromptTemplate.from_template(f'{judge_prompt}'),
                SystemMessagePromptTemplate.from_template(f'{rag_prompt}'),
                HumanMessagePromptTemplate.from_template('{input}')
            ]
        )
        
        return llm_prompt
        
    def chainning(self):
        llm_prompt = self.prompt_engineering()
        chat_chain = LLMChain(
            llm = self.llm_model,
            prompt = llm_prompt
        )
        return chat_chain
    
    def run_llm(self):
        chat_chain = self.chainning()
        predict = chat_chain.predict(input=self.action_result)
        print(predict)
        self.score = predict.split('\n')[0].strip()
        self.reason = predict.split('\n')[1]
        return self.score, self.reason