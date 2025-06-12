// 初始時將 upmsg & processing 清空並隱藏
window.addEventListener('DOMContentLoaded', () => {
  const upmsgEl = document.getElementById('upmsg');
  const procEl  = document.getElementById('processing');
  upmsgEl.textContent               = '';
  upmsgEl.style.display             = 'none';
  upmsgEl.classList.remove('success','error');
  procEl.textContent                = '';
  procEl.style.display              = 'none';
});

// 上傳區塊
document.getElementById('up').onsubmit = async e => {
  e.preventDefault();
  const upmsgEl = document.getElementById('upmsg');
  const procEl  = document.getElementById('processing');

  // 每次按上傳都先隱藏並清空
  upmsgEl.style.display   = 'none';
  upmsgEl.textContent     = '';
  upmsgEl.classList.remove('success','error');
  procEl.style.display    = 'none';
  procEl.textContent      = '';

  const fd  = new FormData(e.target);
  const res = await fetch('/upload', { method: 'POST', body: fd });
  const j   = await res.json();

  // 上傳成功提示
  if (res.ok && j.status === 'ok') {
    upmsgEl.textContent   = '✔️ Upload successful!';
    upmsgEl.classList.add('success');
    upmsgEl.style.display = 'block';
  }

  // 後端錯誤訊息
  if (j.error) {
    upmsgEl.textContent   = j.error;
    upmsgEl.classList.add('error');
    upmsgEl.style.display = 'block';
  }

  // 開始跑 background ingest
  if (j.task_id) {
    procEl.innerHTML     = '<span class="spinner"></span> Processing text…';
    procEl.style.display = 'block';

    const checkStatus = async () => {
      const stRes = await fetch(`/status/${j.task_id}`);
      const st    = await stRes.json();
      if (st.status === 'done') {
        procEl.textContent = '✅ All text has been stored';
      } else if (st.status === 'failed') {
        procEl.textContent = '❌ Storage failed, please try again later';
      } else {
        setTimeout(checkStatus, 2000);
      }
    };
    checkStatus();
  }
};

// 問答區塊
document.getElementById('ask').onclick = async () => {
  const question = document.getElementById('question').value.trim();
  if (!question) return alert('Please enter a question first');

  const ansBox = document.getElementById('answer');
  ansBox.textContent = 'Waiting for response';
  ansBox.classList.add('loading-dots');

  const res = await fetch('/query', {
    method: 'POST',
    headers: { 'Content-Type': 'application/json' },
    body: JSON.stringify({ question })
  });

  const j = await res.json();
  ansBox.classList.remove('loading-dots');
  if (j.error) {
    ansBox.textContent = j.error;
  } else {
    const first = j.sources && j.sources[0];
    let srcText = 'None';
    if (first) srcText = `${first.pdf_name}, page ${first.page}`;
    ansBox.textContent =
      `Answer:\n${j.answer}\n\nSource paragraph: ${srcText}`;
  }
};
