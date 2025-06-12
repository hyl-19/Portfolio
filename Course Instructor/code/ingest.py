import os, time
from collections import defaultdict
from config import textract, ddb_table, UPLOAD_STATUS

def ingest_pdf(bucket: str, key: str, task_id: str):
    try:
        # 啟動 Textract OCR
        resp   = textract.start_document_text_detection(
            DocumentLocation={'S3Object':{'Bucket':bucket,'Name':key}}
        )
        job_id = resp['JobId']
        while True:
            stat = textract.get_document_text_detection(JobId=job_id)
            if stat['JobStatus'] in ['SUCCEEDED','FAILED']:
                break
            time.sleep(2)
        if stat['JobStatus'] != 'SUCCEEDED':
            UPLOAD_STATUS[task_id] = 'failed'; return

        # 收 blocks
        blocks, token = [], None
        while True:
            part = (textract.get_document_text_detection(JobId=job_id, NextToken=token)
                    if token else stat)
            blocks.extend(part.get('Blocks',[]))
            token = part.get('NextToken')
            if not token: break

        # 分頁聚合
        lines_by_page = defaultdict(list)
        for b in blocks:
            if b.get('BlockType')=='LINE':
                pg  = b.get('Page',1)
                txt = b.get('DetectedText') or b.get('Text')
                if txt: lines_by_page[pg].append(txt)

        pdf_name = os.path.basename(key)
        # 寫進 DynamoDB
        with ddb_table.batch_writer() as batch:
            for page, lines in lines_by_page.items():
                page_text = "\n".join(lines)
                batch.put_item(Item={
                    'chunk_id': f"{key}#p{page}",
                    'text'    : page_text,
                    'pdf_name': pdf_name,
                    'page'    : page
                })
        UPLOAD_STATUS[task_id] = 'done'
    except Exception:
        UPLOAD_STATUS[task_id] = 'failed'
