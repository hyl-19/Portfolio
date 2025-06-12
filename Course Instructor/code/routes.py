import uuid
import threading
import traceback
from flask import Blueprint, request, jsonify, render_template
from config import s3, UPLOAD_STATUS
from ingest import ingest_pdf
from query import rag_query
import os

bp = Blueprint('main', __name__)

@bp.route('/')
def home():
    return render_template('index.html')

@bp.route('/upload', methods=['POST'])
def upload():
    # 檢查是否有上傳檔案
    f = request.files.get('pdf')
    if not f:
        return jsonify({'error': 'Choose a PDF file'}), 400

    # 確認環境變數 S3_BUCKET 是否存在
    try:
        bucket_name = os.environ['S3_BUCKET']
    except KeyError:
        return jsonify({'error': 'S3_BUCKET is invalid'}), 500

    # 構造 S3 key 與任務 ID
    key = f"{uuid.uuid4()}_{f.filename}"
    task_id = str(uuid.uuid4())
    UPLOAD_STATUS[task_id] = 'processing'

    # 嘗試上傳到 S3，並捕捉可能的例外
    try:
        s3.upload_fileobj(f, bucket_name, key)
    except Exception as e:
        # 印出完整錯誤堆疊以便除錯
        traceback.print_exc()
        return jsonify({'error': f"S3 upload failed: {str(e)}"}), 500

    # 上傳成功後啟動背景執行緒進行 PDF 文字擷取
    threading.Thread(
        target=ingest_pdf,
        args=(bucket_name, key, task_id),
        daemon=True
    ).start()

    return jsonify({'status': 'ok', 'task_id': task_id})

@bp.route('/status/<task_id>')
def status(task_id):
    st = UPLOAD_STATUS.get(task_id)
    if not st:
        return jsonify({'error': 'error'}), 404
    return jsonify({'status': st})

@bp.route('/query', methods=['POST'])
def query():
    data = request.get_json() or {}
    question = data.get('question', '').strip()
    if not question:
        return jsonify({'error': 'Please offer a question'}), 400

    try:
        answer, first, sources = rag_query(question)
    except Exception as e:
        traceback.print_exc()
        return jsonify({'error': f"Answer Failed: {str(e)}"}), 500

    resp = {'answer': answer}
    if first:
        resp['source'] = f"{first['pdf_name']} page: {first['page']}"
        resp['sources'] = sources
    return jsonify(resp)

@bp.route('/chunks')
def chunks():
    from .config import ddb_table
    try:
        items = ddb_table.scan(Limit=100).get('Items', [])
    except Exception as e:
        traceback.print_exc()
        return jsonify({'error': f"DynamoDB 讀取失敗: {str(e)}"}), 500
    return jsonify(items)
