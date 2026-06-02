# Checklist rápido para envio ao GitHub e MS Teams

## 1. Criar repositório
Crie um repositório novo no GitHub, por exemplo:
`mini-pascal-compiler`

## 2. Subir os arquivos
```bash
git init
git add .
git commit -m "Entrega final do compilador Mini-Pascal"
git branch -M main
git remote add origin <URL_DO_REPOSITORIO>
git push -u origin main
```

## 3. Conferir antes do envio
- README aparece corretamente
- `docs/RELATORIO_FINAL.md` está preenchido
- screenshots estão no repositório
- `tests/out/` contém executáveis e artefatos
- `build/parser.output` foi versionado se o professor exigir

## 4. Enviar no MS Teams
Cole o link do repositório no local solicitado pela disciplina.

> Observação: o assistente não consegue publicar no GitHub em seu nome sem suas credenciais.
