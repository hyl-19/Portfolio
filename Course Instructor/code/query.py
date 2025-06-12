from config import embedder, tokenizer, openai_client, ddb_table, MAX_TOKENS, TOP_K
import faiss

NOT_FOUND = "無法從提供資料中找到答案"

def rag_query(question: str):
    # 拿所有 chunks
    resp  = ddb_table.scan()
    items = resp.get('Items', [])
    texts = [it['text'] for it in items]
    if not texts:
        return NOT_FOUND, [], []

    # embed + FAISS 檢索
    emb   = embedder.encode(texts, normalize_embeddings=True).astype('float32')
    q_emb = embedder.encode([question], normalize_embeddings=True).astype('float32')
    index = faiss.IndexFlatIP(emb.shape[1]); index.add(emb)
    _, I   = index.search(q_emb, TOP_K)

    # 組 context & 來源
    contexts, sources = [], []
    for i in I[0]:
        idx = int(i)
        contexts.append(texts[idx])
        meta = items[idx]
        raw  = meta.get('pdf_name','')
        clean= raw.split('_',1)[1] if '_' in raw else raw
        sources.append({'pdf_name':clean, 'page':meta.get('page',0)})

    # 截斷
    combined = "\n\n".join(contexts)
    toks     = tokenizer.encode(combined)
    if len(toks)>MAX_TOKENS:
        combined = tokenizer.decode(toks[-MAX_TOKENS:])

    # 呼叫 GPT
    sysp = (
        "You are a helpful assistant. Only use provided context. "
        "If insufficient, reply 無法從提供資料中找到答案"
    )
    msg = [
        {'role':'system','content':sysp},
        {'role':'user','content':f"Context:\n{combined}\n\nQuestion: {question}"}
    ]
    res = openai_client.chat.completions.create(
        model='gpt-4o-mini', messages=msg,
        temperature=0.2, max_tokens=256
    )
    answer = res.choices[0].message.content.strip()
    if answer.startswith(NOT_FOUND):
        return answer, None, []
    first = sources[0] if sources else None
    return answer, first, sources
