def generate_html(pie_chart_path, bar_chart_path, top_5_sounds, top_5_continuous_sounds, html_file_path):
    # 函数来生成声音列表的HTML项
    def generate_sound_list(sounds, continuous=False):
        list_items = ""
        for i, sound in enumerate(sounds):
            if continuous:
                list_items += f'<li style="font-size: 24px;">{i + 1}. {sound[0]}: {sound[1]} consecutive occurrences</li>\n'
            else:
                list_items += f'<li style="font-size: 24px;">{i + 1}. {sound["Sound"]}: {sound["Count"]} occurrences</li>\n'
        return list_items

    # 生成声音出现次数列表
    sound_list_html = generate_sound_list(top_5_sounds.to_dict('records'), continuous=False)
    
    # 生成连续出现最多的声音列表
    continuous_sound_list_html = generate_sound_list(top_5_continuous_sounds, continuous=True)
    
    html_content = f"""
    <html>
    <head>
    <title>Environment Sounds Analysis and Statistics</title>
    <style>
    .container {{
        display: flex;
        justify-content: space-between;
        padding: 10px;
    }}
    .statistics {{
        width: 90%;  /* 左半邊 */
        padding: 20px;
        font-size: 32px;
    }}
    h1 {{
        font-size: 48px;  /* 修改標題字體大小 */
        font-weight: bold;
        margin-bottom: 5px;  /* 減少標題和內容之間的空白 */
    }}
    .charts {{
        display: flex;
        flex-direction: column;
        align-items: flex-start;  /* 圖片向左對齊 */
        padding: 20px;
    }}
    .chart {{
        padding: 10px;
    }}
    img {{
        max-width: 100%;  /* 限制圖片的寬度 */
        height: auto;
    }}
    ul {{
        list-style-type: none; /* 去掉列表前的符號 */
    }}
    li {{
        font-size: 32px;
        margin-bottom: 5px;
    }}
    .top-section {{
        display: flex;
        justify-content: space-between;
        width: 100%;
        margin-bottom: 20px;
    }}
    .top-section .statistics:nth-child(2) {{
        align-items: flex-start; /* 讓右邊的文字靠左對齊 */
    }}
    .bottom-section {{
        display: flex;
        flex-direction: column;
        align-items: flex-start;  /* 圖片向左對齊 */
        width: 100%;
    }}
    </style>
    </head>
    <body>
    <h1>Sound Statistics</h1>

    <div class="top-section">
        <div class="statistics">
            <p class="subtitle">Top {min(5, len(top_5_sounds))} most frequent sounds:</p>
            <ul>
                {sound_list_html}
            </ul>
        </div>

        <div class="statistics">
            <p class="subtitle">Top {min(5, len(top_5_continuous_sounds))} longest continuous sounds:</p>
            <ul>
                {continuous_sound_list_html}
            </ul>
        </div>
    </div>

    <div class="bottom-section">
        <div class="chart">
            <img src="{pie_chart_path}" alt="Pie Chart">
        </div>
        <div class="chart">
            <img src="{bar_chart_path}" alt="Bar Chart">
        </div>
    </div>

    </body>
    </html>
    """

    # 将HTML内容写入文件
    with open(html_file_path, 'w', encoding='utf-8') as file:
        file.write(html_content)

    print(f"HTML file has been saved as {html_file_path}")
